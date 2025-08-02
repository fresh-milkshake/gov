#include "parser.h"
#include <iostream>

Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)), current(0) {}

Token Parser::peek() {
    return tokens[current];
}

Token Parser::previous() {
    return tokens[current - 1];
}

bool Parser::isAtEnd() {
    return peek().type == TokenType::EOF_TOKEN;
}

bool Parser::check(TokenType type) {
    if (isAtEnd()) return false;
    return peek().type == type;
}

bool Parser::match(std::initializer_list<TokenType> types) {
    for (TokenType type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

Token Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) return advance();
    
    std::cerr << "Parse error: " << message << " at line " << peek().line << std::endl;
    return peek();
}

void Parser::skipNewlines() {
    while (match({TokenType::NEWLINE})) {}
}

std::unique_ptr<Expression> Parser::expression() {
    return logicalOr();
}

std::unique_ptr<Expression> Parser::logicalOr() {
    auto expr = logicalAnd();
    
    while (true) {
        skipNewlines();
        if (match({TokenType::OR})) {
            TokenType op = previous().type;
            skipNewlines();
            auto right = logicalAnd();
            expr = std::make_unique<BinaryOp>(std::move(expr), op, std::move(right));
        } else {
            break;
        }
    }
    
    return expr;
}

std::unique_ptr<Expression> Parser::logicalAnd() {
    auto expr = equality();
    
    while (true) {
        skipNewlines();
        if (match({TokenType::AND})) {
            TokenType op = previous().type;
            skipNewlines();
            auto right = equality();
            expr = std::make_unique<BinaryOp>(std::move(expr), op, std::move(right));
        } else {
            break;
        }
    }
    
    return expr;
}

std::unique_ptr<Expression> Parser::equality() {
    auto expr = addition();
    
    while (true) {
        skipNewlines();
        if (match({TokenType::EQUALS, TokenType::NOT_EQUALS, TokenType::LESS_THAN})) {
            TokenType op = previous().type;
            skipNewlines();
            auto right = addition();
            expr = std::make_unique<BinaryOp>(std::move(expr), op, std::move(right));
        } else {
            break;
        }
    }
    
    return expr;
}

std::unique_ptr<Expression> Parser::addition() {
    auto expr = multiplication();
    
    while (true) {
        skipNewlines();
        if (match({TokenType::PLUS, TokenType::MINUS})) {
            TokenType op = previous().type;
            skipNewlines();
            auto right = multiplication();
            expr = std::make_unique<BinaryOp>(std::move(expr), op, std::move(right));
        } else {
            break;
        }
    }
    
    return expr;
}

std::unique_ptr<Expression> Parser::multiplication() {
    auto expr = primary();
    
    while (true) {
        skipNewlines();
        if (match({TokenType::MULTIPLY, TokenType::DIVIDE})) {
            TokenType op = previous().type;
            skipNewlines();
            auto right = primary();
            expr = std::make_unique<BinaryOp>(std::move(expr), op, std::move(right));
        } else {
            break;
        }
    }
    
    return expr;
}

std::unique_ptr<Expression> Parser::primary() {
    if (match({TokenType::STRING})) {
        return std::make_unique<StringLiteral>(previous().value);
    }
    
    if (match({TokenType::INTEGER})) {
        return std::make_unique<IntegerLiteral>(std::stoi(previous().value));
    }
    
    if (match({TokenType::LEFT_PAREN})) {
        auto expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expected ')' after expression");
        return expr;
    }
    
    if (match({TokenType::IDENTIFIER})) {
        std::string name = previous().value;
        
        if (match({TokenType::LEFT_BRACKET})) {
            auto index = expression();
            consume(TokenType::RIGHT_BRACKET, "Expected ']' after array index");
            return std::make_unique<ArrayAccess>(std::make_unique<Identifier>(name), std::move(index));
        }
        
        return std::make_unique<Identifier>(name);
    }
    
    std::cerr << "Expected expression at line " << peek().line << std::endl;
    return nullptr;
}

std::unique_ptr<Statement> Parser::statement() {
    skipNewlines();
    
    if (match({TokenType::PRAISE_LEADER})) {
        return printStatement();
    }
    
    if (match({TokenType::PLEASE})) {
        if (match({TokenType::DECLARE_VARIABLE})) {
            return varDeclaration();
        } else if (match({TokenType::SET})) {
            return assignment();
        } else if (match({TokenType::INCREMENT})) {
            return incrementStatement();
        } else if (match({TokenType::READ})) {
            return readStatement();
        }
    }
    
    if (match({TokenType::FOR_THE_PEOPLE})) {
        return forLoop();
    }
    
    if (match({TokenType::WHILE})) {
        return whileLoop();
    }
    
    if (match({TokenType::IF})) {
        return ifStatement();
    }
    
    // Skip comments and other tokens
    if (match({TokenType::OBEY_PARTY_LINE, TokenType::DENOUNCE_IMPERIALIST_ERRORS})) {
        // Skip to end of line
        while (!check(TokenType::NEWLINE) && !isAtEnd()) {
            advance();
        }
        return nullptr;
    }
    
    return nullptr;
}

std::unique_ptr<Statement> Parser::printStatement() {
    auto expr = expression();
    return std::make_unique<PrintStatement>(std::move(expr));
}

std::unique_ptr<Statement> Parser::varDeclaration() {
    consume(TokenType::STRING, "Expected variable name in quotes");
    std::string name = previous().value;
    
    consume(TokenType::AS, "Expected 'AS' after variable name");
    
    std::string type;
    int arraySize = 0;
    
    if (match({TokenType::INTEGER_TYPE})) {
        type = "INTEGER";
    } else if (match({TokenType::STRING_TYPE})) {
        type = "STRING";
    } else if (match({TokenType::ARRAY_OF_STRING})) {
        type = "ARRAY_OF_STRING";
        consume(TokenType::SIZE, "Expected 'SIZE' after ARRAY_OF_STRING");
        consume(TokenType::INTEGER, "Expected array size");
        arraySize = std::stoi(previous().value);
    }
    
    return std::make_unique<VarDeclaration>(name, type, arraySize);
}

std::unique_ptr<Statement> Parser::assignment() {
    consume(TokenType::IDENTIFIER, "Expected variable name");
    std::string varName = previous().value;
    
    std::unique_ptr<Expression> index = nullptr;
    if (match({TokenType::LEFT_BRACKET})) {
        index = expression();
        consume(TokenType::RIGHT_BRACKET, "Expected ']' after array index");
    }
    
    consume(TokenType::TO, "Expected 'TO' in assignment");
    auto value = expression();
    
    return std::make_unique<Assignment>(varName, std::move(value), std::move(index));
}

std::unique_ptr<Statement> Parser::forLoop() {
    // Parse the full condition expression (e.g., "GloriousCounter LESS_THAN 3")
    auto condition = expression();
    consume(TokenType::DO, "Expected 'DO' after for condition");
    
    // For now, we'll use an empty string for varName since the condition contains the variable
    auto loop = std::make_unique<ForLoop>("", std::move(condition));
    
    skipNewlines();
    while (!check(TokenType::END_FOR_THE_PEOPLE) && !isAtEnd()) {
        auto stmt = statement();
        if (stmt) {
            loop->body.push_back(std::move(stmt));
        }
        skipNewlines();
    }
    
    consume(TokenType::END_FOR_THE_PEOPLE, "Expected 'END_FOR_THE_PEOPLE'");
    
    return std::move(loop);
}

std::unique_ptr<Statement> Parser::whileLoop() {
    auto condition = expression();
    consume(TokenType::DO, "Expected 'DO' after while condition");
    
    auto loop = std::make_unique<WhileLoop>(std::move(condition));
    
    skipNewlines();
    while (!check(TokenType::END_WHILE) && !isAtEnd()) {
        auto stmt = statement();
        if (stmt) {
            loop->body.push_back(std::move(stmt));
        }
        skipNewlines();
    }
    
    consume(TokenType::END_WHILE, "Expected 'END_WHILE'");
    
    return std::move(loop);
}

std::unique_ptr<Statement> Parser::ifStatement() {
    auto condition = expression();
    consume(TokenType::THEN, "Expected 'THEN' after if condition");
    
    auto ifStmt = std::make_unique<IfStatement>(std::move(condition));
    
    skipNewlines();
    while (!check(TokenType::ELSE_IF) && !check(TokenType::ELSE) && !check(TokenType::END_IF) && !isAtEnd()) {
        auto stmt = statement();
        if (stmt) {
            ifStmt->thenBranch.push_back(std::move(stmt));
        }
        skipNewlines();
    }
    
    // Handle ELSE_IF clauses
    while (match({TokenType::ELSE_IF})) {
        auto elseIfCondition = expression();
        consume(TokenType::THEN, "Expected 'THEN' after else-if condition");
        
        ElseIfClause elseIfClause(std::move(elseIfCondition));
        
        skipNewlines();
        while (!check(TokenType::ELSE_IF) && !check(TokenType::ELSE) && !check(TokenType::END_IF) && !isAtEnd()) {
            auto stmt = statement();
            if (stmt) {
                elseIfClause.body.push_back(std::move(stmt));
            }
            skipNewlines();
        }
        
        ifStmt->elseIfClauses.push_back(std::move(elseIfClause));
    }
    
    if (match({TokenType::ELSE})) {
        skipNewlines();
        while (!check(TokenType::END_IF) && !isAtEnd()) {
            auto stmt = statement();
            if (stmt) {
                ifStmt->elseBranch.push_back(std::move(stmt));
            }
            skipNewlines();
        }
    }
    
    consume(TokenType::END_IF, "Expected 'END_IF'");
    
    return std::move(ifStmt);
}

std::unique_ptr<Statement> Parser::incrementStatement() {
    consume(TokenType::IDENTIFIER, "Expected variable name");
    std::string varName = previous().value;
    
    consume(TokenType::BY, "Expected 'BY' after INCREMENT");
    consume(TokenType::INTEGER, "Expected increment amount");
    int amount = std::stoi(previous().value);
    
    return std::make_unique<IncrementStatement>(varName, amount);
}

std::unique_ptr<Statement> Parser::readStatement() {
    consume(TokenType::IDENTIFIER, "Expected variable name");
    std::string varName = previous().value;
    
    return std::make_unique<ReadStatement>(varName);
}

std::unique_ptr<Program> Parser::parse() {
    auto program = std::make_unique<Program>();
    
    // Skip initial header
    if (match({TokenType::I_LOVE_GOVERNMENT})) {
        skipNewlines();
    }
    
    while (!isAtEnd()) {
        try {
            auto stmt = statement();
            if (stmt) {
                program->statements.push_back(std::move(stmt));
            }
            skipNewlines();
        } catch (...) {
            std::cerr << "Exception during parsing at token " << current << std::endl;
            return nullptr;
        }
    }
    
    return program;
}