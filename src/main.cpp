#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

struct Config {
    std::string command = "run";
    std::string filename;
    int debugLevel = 0;
    bool stepByStep = false;
};

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return "";
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void printHelp(const std::string& programName) {
    std::cout << "Gov Language Interpreter\n\n";
    std::cout << "Usage: " << programName << " [COMMAND] [OPTIONS] <filename.gov>\n\n";
    std::cout << "Commands:\n";
    std::cout << "  run       Interpret and execute the code (default)\n";
    std::cout << "  parse     Show the parsed AST structure\n";
    std::cout << "  debug     Show detailed runtime information\n\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help           Show this help message\n";
    std::cout << "  -v, --verbose LEVEL  Set debug verbosity level (0-3, default: 1 for debug, 0 for run)\n";
    std::cout << "  -s, --step           Enable step-by-step execution in debug mode\n\n";
    std::cout << "Examples:\n";
    std::cout << "  " << programName << " hello_world.gov\n";
    std::cout << "  " << programName << " run hello_world.gov\n";
    std::cout << "  " << programName << " parse hello_world.gov\n";
    std::cout << "  " << programName << " debug -v 2 -s hello_world.gov\n";
}

Config parseArgs(int argc, char* argv[]) {
    Config config;
    std::vector<std::string> args;
    bool verbosityExplicitlySet = false;
    
    for (int i = 1; i < argc; i++) {
        args.push_back(argv[i]);
    }
    
    if (args.empty()) {
        std::cerr << "Error: No arguments provided\n";
        printHelp(argv[0]);
        exit(1);
    }
    
    // Check for help
    for (const auto& arg : args) {
        if (arg == "-h" || arg == "--help") {
            printHelp(argv[0]);
            exit(0);
        }
    }
    
    size_t i = 0;
    
    // Check if first argument is a command
    if (args[i] == "run" || args[i] == "parse" || args[i] == "debug") {
        config.command = args[i];
        i++;
    }
    
    // Parse options
    while (i < args.size()) {
        if (args[i] == "-v" || args[i] == "--verbose") {
            if (i + 1 >= args.size()) {
                std::cerr << "Error: --verbose requires a level argument\n";
                exit(1);
            }
            try {
                config.debugLevel = std::stoi(args[i + 1]);
                if (config.debugLevel < 0) config.debugLevel = 0;
                if (config.debugLevel > 3) config.debugLevel = 3;
                verbosityExplicitlySet = true;
            } catch (const std::exception&) {
                std::cerr << "Error: Invalid debug level. Must be a number 0-3\n";
                exit(1);
            }
            i += 2;
        } else if (args[i] == "-s" || args[i] == "--step") {
            config.stepByStep = true;
            i++;
        } else if (args[i][0] == '-') {
            std::cerr << "Error: Unknown option " << args[i] << "\n";
            exit(1);
        } else {
            // This should be the filename
            config.filename = args[i];
            i++;
            break;
        }
    }
    
    if (config.filename.empty()) {
        std::cerr << "Error: No filename provided\n";
        printHelp(argv[0]);
        exit(1);
    }
    
    // Set default debug level to 1 if debug command is used without explicit verbosity
    if (config.command == "debug" && !verbosityExplicitlySet) {
        config.debugLevel = 1;
    }
    
    return config;
}

void printAST(ASTNode* node, int indent = 0) {
    std::string indentStr(indent * 2, ' ');
    
    if (auto program = dynamic_cast<Program*>(node)) {
        std::cout << indentStr << "Program (" << program->statements.size() << " statements)\n";
        for (const auto& stmt : program->statements) {
            printAST(stmt.get(), indent + 1);
        }
    } else if (auto print = dynamic_cast<PrintStatement*>(node)) {
        std::cout << indentStr << "PrintStatement\n";
        printAST(print->expr.get(), indent + 1);
    } else if (auto varDecl = dynamic_cast<VarDeclaration*>(node)) {
        std::cout << indentStr << "VarDeclaration: " << varDecl->name 
                  << " (type: " << varDecl->type;
        if (varDecl->arraySize > 0) {
            std::cout << "[" << varDecl->arraySize << "]";
        }
        std::cout << ")\n";
    } else if (auto assign = dynamic_cast<Assignment*>(node)) {
        std::cout << indentStr << "Assignment: " << assign->varName << "\n";
        if (assign->index) {
            std::cout << indentStr << "  Index:\n";
            printAST(assign->index.get(), indent + 2);
        }
        std::cout << indentStr << "  Value:\n";
        printAST(assign->value.get(), indent + 2);
    } else if (auto forLoop = dynamic_cast<ForLoop*>(node)) {
        std::cout << indentStr << "ForLoop: " << forLoop->varName << "\n";
        std::cout << indentStr << "  Condition:\n";
        printAST(forLoop->condition.get(), indent + 2);
        std::cout << indentStr << "  Body (" << forLoop->body.size() << " statements):\n";
        for (const auto& stmt : forLoop->body) {
            printAST(stmt.get(), indent + 2);
        }
    } else if (auto whileLoop = dynamic_cast<WhileLoop*>(node)) {
        std::cout << indentStr << "WhileLoop\n";
        std::cout << indentStr << "  Condition:\n";
        printAST(whileLoop->condition.get(), indent + 2);
        std::cout << indentStr << "  Body (" << whileLoop->body.size() << " statements):\n";
        for (const auto& stmt : whileLoop->body) {
            printAST(stmt.get(), indent + 2);
        }
    } else if (auto ifStmt = dynamic_cast<IfStatement*>(node)) {
        std::cout << indentStr << "IfStatement\n";
        std::cout << indentStr << "  Condition:\n";
        printAST(ifStmt->condition.get(), indent + 2);
        std::cout << indentStr << "  Then (" << ifStmt->thenBranch.size() << " statements):\n";
        for (const auto& stmt : ifStmt->thenBranch) {
            printAST(stmt.get(), indent + 2);
        }
        if (!ifStmt->elseIfClauses.empty()) {
            std::cout << indentStr << "  ElseIf clauses (" << ifStmt->elseIfClauses.size() << "):\n";
            for (const auto& clause : ifStmt->elseIfClauses) {
                std::cout << indentStr << "    Condition:\n";
                printAST(clause.condition.get(), indent + 3);
                std::cout << indentStr << "    Body (" << clause.body.size() << " statements):\n";
                for (const auto& stmt : clause.body) {
                    printAST(stmt.get(), indent + 3);
                }
            }
        }
        if (!ifStmt->elseBranch.empty()) {
            std::cout << indentStr << "  Else (" << ifStmt->elseBranch.size() << " statements):\n";
            for (const auto& stmt : ifStmt->elseBranch) {
                printAST(stmt.get(), indent + 2);
            }
        }
    } else if (auto inc = dynamic_cast<IncrementStatement*>(node)) {
        std::cout << indentStr << "IncrementStatement: " << inc->varName 
                  << " (amount: " << inc->amount << ")\n";
    } else if (auto read = dynamic_cast<ReadStatement*>(node)) {
        std::cout << indentStr << "ReadStatement: " << read->varName << "\n";
    } else if (auto binOp = dynamic_cast<BinaryOp*>(node)) {
        std::cout << indentStr << "BinaryOp (";
        switch (binOp->op) {
            case TokenType::PLUS: std::cout << "+"; break;
            case TokenType::MINUS: std::cout << "-"; break;
            case TokenType::MULTIPLY: std::cout << "*"; break;
            case TokenType::DIVIDE: std::cout << "/"; break;
            case TokenType::EQUALS: std::cout << "=="; break;
            case TokenType::NOT_EQUALS: std::cout << "!="; break;
            case TokenType::LESS_THAN: std::cout << "<"; break;
            case TokenType::AND: std::cout << "&&"; break;
            case TokenType::OR: std::cout << "||"; break;
            default: std::cout << "unknown(" << static_cast<int>(binOp->op) << ")"; break;
        }
        std::cout << ")\n";
        std::cout << indentStr << "  Left:\n";
        printAST(binOp->left.get(), indent + 2);
        std::cout << indentStr << "  Right:\n";
        printAST(binOp->right.get(), indent + 2);
    } else if (auto str = dynamic_cast<StringLiteral*>(node)) {
        std::cout << indentStr << "StringLiteral: \"" << str->value << "\"\n";
    } else if (auto num = dynamic_cast<IntegerLiteral*>(node)) {
        std::cout << indentStr << "IntegerLiteral: " << num->value << "\n";
    } else if (auto id = dynamic_cast<Identifier*>(node)) {
        std::cout << indentStr << "Identifier: " << id->name << "\n";
    } else if (auto arr = dynamic_cast<ArrayAccess*>(node)) {
        std::cout << indentStr << "ArrayAccess\n";
        std::cout << indentStr << "  Array:\n";
        printAST(arr->array.get(), indent + 2);
        std::cout << indentStr << "  Index:\n";
        printAST(arr->index.get(), indent + 2);
    } else {
        std::cout << indentStr << "Unknown AST Node\n";
    }
}

int main(int argc, char* argv[]) {
    Config config = parseArgs(argc, argv);
    
    std::string source = readFile(config.filename);
    if (source.empty()) {
        return 1;
    }
    
    if (config.debugLevel > 0) {
        std::cout << "Source loaded: " << source.length() << " characters" << std::endl;
    }
    
    // Tokenize
    Lexer lexer(source);
    auto tokens = lexer.tokenize();
    
    if (config.debugLevel > 0) {
        std::cout << "Tokens generated: " << tokens.size() << std::endl;
    }
    
    if (config.debugLevel > 1) {
        std::cout << "\nTokens:\n";
        for (size_t i = 0; i < tokens.size(); i++) {
            std::cout << "  [" << i << "] ";
            switch (tokens[i].type) {
                case TokenType::IDENTIFIER: std::cout << "IDENTIFIER"; break;
                case TokenType::INTEGER: std::cout << "INTEGER"; break;
                case TokenType::STRING: std::cout << "STRING"; break;
                case TokenType::PLUS: std::cout << "PLUS"; break;
                case TokenType::MINUS: std::cout << "MINUS"; break;
                case TokenType::MULTIPLY: std::cout << "MULTIPLY"; break;
                case TokenType::DIVIDE: std::cout << "DIVIDE"; break;
                case TokenType::EQUALS: std::cout << "EQUALS"; break;
                case TokenType::NOT_EQUALS: std::cout << "NOT_EQUALS"; break;
                case TokenType::LESS_THAN: std::cout << "LESS_THAN"; break;
                case TokenType::AND: std::cout << "AND"; break;
                case TokenType::OR: std::cout << "OR"; break;
                case TokenType::LEFT_PAREN: std::cout << "LEFT_PAREN"; break;
                case TokenType::RIGHT_PAREN: std::cout << "RIGHT_PAREN"; break;
                case TokenType::LEFT_BRACKET: std::cout << "LEFT_BRACKET"; break;
                case TokenType::RIGHT_BRACKET: std::cout << "RIGHT_BRACKET"; break;
                case TokenType::NEWLINE: std::cout << "NEWLINE"; break;
                case TokenType::EOF_TOKEN: std::cout << "EOF_TOKEN"; break;
                case TokenType::I_LOVE_GOVERNMENT: std::cout << "I_LOVE_GOVERNMENT"; break;
                case TokenType::PRAISE_LEADER: std::cout << "PRAISE_LEADER"; break;
                case TokenType::OBEY_PARTY_LINE: std::cout << "OBEY_PARTY_LINE"; break;
                case TokenType::PLEASE: std::cout << "PLEASE"; break;
                case TokenType::DECLARE_VARIABLE: std::cout << "DECLARE_VARIABLE"; break;
                case TokenType::AS: std::cout << "AS"; break;
                case TokenType::INTEGER_TYPE: std::cout << "INTEGER_TYPE"; break;
                case TokenType::STRING_TYPE: std::cout << "STRING_TYPE"; break;
                case TokenType::ARRAY_OF_STRING: std::cout << "ARRAY_OF_STRING"; break;
                case TokenType::SIZE: std::cout << "SIZE"; break;
                case TokenType::SET: std::cout << "SET"; break;
                case TokenType::TO: std::cout << "TO"; break;
                case TokenType::FOR_THE_PEOPLE: std::cout << "FOR_THE_PEOPLE"; break;
                case TokenType::DO: std::cout << "DO"; break;
                case TokenType::END_FOR_THE_PEOPLE: std::cout << "END_FOR_THE_PEOPLE"; break;
                case TokenType::INCREMENT: std::cout << "INCREMENT"; break;
                case TokenType::BY: std::cout << "BY"; break;
                case TokenType::DENOUNCE_IMPERIALIST_ERRORS: std::cout << "DENOUNCE_IMPERIALIST_ERRORS"; break;
                case TokenType::WHILE: std::cout << "WHILE"; break;
                case TokenType::IF: std::cout << "IF"; break;
                case TokenType::THEN: std::cout << "THEN"; break;
                case TokenType::ELSE: std::cout << "ELSE"; break;
                case TokenType::ELSE_IF: std::cout << "ELSE_IF"; break;
                case TokenType::END_IF: std::cout << "END_IF"; break;
                case TokenType::END_WHILE: std::cout << "END_WHILE"; break;
                case TokenType::READ: std::cout << "READ"; break;
                default: std::cout << "UNKNOWN(" << static_cast<int>(tokens[i].type) << ")"; break;
            }
            std::cout << " \"" << tokens[i].value << "\"\n";
        }
        std::cout << std::endl;
    }
    
    // Parse
    Parser parser(std::move(tokens));
    auto program = parser.parse();
    
    if (!program) {
        std::cerr << "Parse error occurred" << std::endl;
        return 1;
    }
    
    if (config.debugLevel > 0) {
        std::cout << "Program parsed successfully with " << program->statements.size() << " statements" << std::endl;
    }
    
    // Execute based on command
    if (config.command == "parse") {
        std::cout << "\nAbstract Syntax Tree:\n";
        std::cout << "=====================\n";
        printAST(program.get());
        return 0;
    }
    
    // For run and debug commands
    Interpreter interpreter;
    
    if (config.command == "debug") {
        std::cout << "\nDebug Mode (Level " << config.debugLevel << ")\n";
        std::cout << "=====================================\n";
        
        if (config.stepByStep) {
            std::cout << "Step-by-step execution enabled. Press Enter to continue after each step.\n\n";
        }
        
        interpreter.setDebugMode(true, config.debugLevel, config.stepByStep);
    }
    
    interpreter.interpret(program.get());
    
    return 0;
}