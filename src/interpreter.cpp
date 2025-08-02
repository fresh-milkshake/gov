#include "interpreter.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Value Interpreter::evaluate(Expression* expr) {
    if (auto literal = dynamic_cast<StringLiteral*>(expr)) {
        return literal->value;
    }
    
    if (auto literal = dynamic_cast<IntegerLiteral*>(expr)) {
        return literal->value;
    }
    
    if (auto id = dynamic_cast<Identifier*>(expr)) {
        auto it = variables.find(id->name);
        if (it != variables.end()) {
            return it->second;
        }
        std::cerr << "Undefined variable: " << id->name << std::endl;
        return 0;
    }
    
    if (auto access = dynamic_cast<ArrayAccess*>(expr)) {
        auto arrayValue = evaluate(access->array.get());
        auto indexValue = evaluate(access->index.get());
        
        if (std::holds_alternative<std::vector<std::string>>(arrayValue) && 
            std::holds_alternative<int>(indexValue)) {
            auto& arr = std::get<std::vector<std::string>>(arrayValue);
            int idx = std::get<int>(indexValue);
            if (idx >= 0 && idx < arr.size()) {
                return arr[idx];
            }
        }
        return std::string("");
    }
    
    if (auto binOp = dynamic_cast<BinaryOp*>(expr)) {
        auto left = evaluate(binOp->left.get());
        auto right = evaluate(binOp->right.get());
        return binaryOperation(left, binOp->op, right);
    }
    
    return 0;
}

void Interpreter::execute(Statement* stmt) {
    if (auto print = dynamic_cast<PrintStatement*>(stmt)) {
        auto value = evaluate(print->expr.get());
        std::cout << valueToString(value) << std::endl;
        return;
    }
    
    if (auto decl = dynamic_cast<VarDeclaration*>(stmt)) {
        if (decl->type == "INTEGER") {
            variables[decl->name] = 0;
        } else if (decl->type == "STRING") {
            variables[decl->name] = std::string("");
        } else if (decl->type == "ARRAY_OF_STRING") {
            variables[decl->name] = std::vector<std::string>(decl->arraySize, " ");
        }
        return;
    }
    
    if (auto assign = dynamic_cast<Assignment*>(stmt)) {
        auto value = evaluate(assign->value.get());
        
        if (assign->index) {
            // Array assignment
            auto it = variables.find(assign->varName);
            if (it != variables.end() && std::holds_alternative<std::vector<std::string>>(it->second)) {
                auto indexValue = evaluate(assign->index.get());
                if (std::holds_alternative<int>(indexValue)) {
                    auto& arr = std::get<std::vector<std::string>>(it->second);
                    int idx = std::get<int>(indexValue);
                    if (idx >= 0 && idx < arr.size()) {
                        arr[idx] = valueToString(value);
                    }
                }
            }
        } else {
            // Regular assignment
            variables[assign->varName] = value;
        }
        return;
    }
    
    if (auto forLoop = dynamic_cast<ForLoop*>(stmt)) {
        while (isTruthy(evaluate(forLoop->condition.get()))) {
            for (auto& bodyStmt : forLoop->body) {
                execute(bodyStmt.get());
            }
        }
        return;
    }
    
    if (auto whileLoop = dynamic_cast<WhileLoop*>(stmt)) {
        while (isTruthy(evaluate(whileLoop->condition.get()))) {
            for (auto& bodyStmt : whileLoop->body) {
                execute(bodyStmt.get());
            }
        }
        return;
    }
    
    if (auto ifStmt = dynamic_cast<IfStatement*>(stmt)) {
        if (isTruthy(evaluate(ifStmt->condition.get()))) {
            for (auto& thenStmt : ifStmt->thenBranch) {
                execute(thenStmt.get());
            }
        } else {
            // Check ELSE_IF clauses
            bool executed = false;
            for (auto& elseIfClause : ifStmt->elseIfClauses) {
                if (isTruthy(evaluate(elseIfClause.condition.get()))) {
                    for (auto& elseIfStmt : elseIfClause.body) {
                        execute(elseIfStmt.get());
                    }
                    executed = true;
                    break;
                }
            }
            
            // If no ELSE_IF was executed, run ELSE branch
            if (!executed) {
                for (auto& elseStmt : ifStmt->elseBranch) {
                    execute(elseStmt.get());
                }
            }
        }
        return;
    }
    
    if (auto inc = dynamic_cast<IncrementStatement*>(stmt)) {
        auto it = variables.find(inc->varName);
        if (it != variables.end() && std::holds_alternative<int>(it->second)) {
            int currentValue = std::get<int>(it->second);
            it->second = currentValue + inc->amount;
        }
        return;
    }
    
    if (auto read = dynamic_cast<ReadStatement*>(stmt)) {
        std::string input;
        std::getline(std::cin, input);
        
        // Try to parse as integer first
        try {
            int intValue = std::stoi(input);
            variables[read->varName] = intValue;
        } catch (...) {
            variables[read->varName] = input;
        }
        return;
    }
}

std::string Interpreter::valueToString(const Value& val) {
    if (std::holds_alternative<int>(val)) {
        return std::to_string(std::get<int>(val));
    } else if (std::holds_alternative<std::string>(val)) {
        return std::get<std::string>(val);
    } else if (std::holds_alternative<std::vector<std::string>>(val)) {
        auto& arr = std::get<std::vector<std::string>>(val);
        std::stringstream ss;
        ss << "[";
        for (size_t i = 0; i < arr.size(); ++i) {
            if (i > 0) ss << ", ";
            ss << arr[i];
        }
        ss << "]";
        return ss.str();
    }
    return "";
}

bool Interpreter::isTruthy(const Value& val) {
    if (std::holds_alternative<int>(val)) {
        return std::get<int>(val) != 0;
    } else if (std::holds_alternative<std::string>(val)) {
        return !std::get<std::string>(val).empty();
    }
    return false;
}

Value Interpreter::binaryOperation(const Value& left, TokenType op, const Value& right) {
    switch (op) {
        case TokenType::PLUS:
            if (std::holds_alternative<std::string>(left) || std::holds_alternative<std::string>(right)) {
                return valueToString(left) + valueToString(right);
            } else if (std::holds_alternative<int>(left) && std::holds_alternative<int>(right)) {
                return std::get<int>(left) + std::get<int>(right);
            }
            break;
            
        case TokenType::MINUS:
            if (std::holds_alternative<int>(left) && std::holds_alternative<int>(right)) {
                return std::get<int>(left) - std::get<int>(right);
            }
            break;
            
        case TokenType::EQUALS:
            return (valueToString(left) == valueToString(right)) ? 1 : 0;
            
        case TokenType::NOT_EQUALS:
            return (valueToString(left) != valueToString(right)) ? 1 : 0;
            
        case TokenType::LESS_THAN:
            if (std::holds_alternative<int>(left) && std::holds_alternative<int>(right)) {
                return (std::get<int>(left) < std::get<int>(right)) ? 1 : 0;
            }
            break;
            
        case TokenType::MULTIPLY:
            if (std::holds_alternative<int>(left) && std::holds_alternative<int>(right)) {
                return std::get<int>(left) * std::get<int>(right);
            }
            break;
            
        case TokenType::DIVIDE:
            if (std::holds_alternative<int>(left) && std::holds_alternative<int>(right)) {
                int rightVal = std::get<int>(right);
                if (rightVal != 0) {
                    return std::get<int>(left) / rightVal;
                }
            }
            break;
            
        case TokenType::AND:
            return (isTruthy(left) && isTruthy(right)) ? 1 : 0;
            
        case TokenType::OR:
            return (isTruthy(left) || isTruthy(right)) ? 1 : 0;
    }
    
    return 0;
}

void Interpreter::debugPrint(const std::string& message, int level) {
    if (debugMode && debugLevel >= level) {
        std::cout << "[DEBUG] " << message << std::endl;
    }
}

void Interpreter::debugPrintVariables() {
    if (!debugMode || debugLevel < 2) return;
    
    std::cout << "[DEBUG] Variables:\n";
    if (variables.empty()) {
        std::cout << "[DEBUG]   (none)\n";
    } else {
        for (const auto& [name, value] : variables) {
            std::cout << "[DEBUG]   " << name << " = " << valueToString(value) << "\n";
        }
    }
}

void Interpreter::debugPrintStatement(Statement* stmt) {
    if (!debugMode || debugLevel < 1) return;
    
    std::cout << "[DEBUG] Executing statement #" << currentStatement << ": ";
    
    if (dynamic_cast<PrintStatement*>(stmt)) {
        std::cout << "PRINT";
    } else if (dynamic_cast<VarDeclaration*>(stmt)) {
        auto decl = dynamic_cast<VarDeclaration*>(stmt);
        std::cout << "VAR_DECLARATION (" << decl->name << " : " << decl->type << ")";
    } else if (dynamic_cast<Assignment*>(stmt)) {
        auto assign = dynamic_cast<Assignment*>(stmt);
        std::cout << "ASSIGNMENT (" << assign->varName << ")";
    } else if (dynamic_cast<ForLoop*>(stmt)) {
        std::cout << "FOR_LOOP";
    } else if (dynamic_cast<WhileLoop*>(stmt)) {
        std::cout << "WHILE_LOOP";
    } else if (dynamic_cast<IfStatement*>(stmt)) {
        std::cout << "IF_STATEMENT";
    } else if (dynamic_cast<IncrementStatement*>(stmt)) {
        auto inc = dynamic_cast<IncrementStatement*>(stmt);
        std::cout << "INCREMENT (" << inc->varName << " += " << inc->amount << ")";
    } else if (dynamic_cast<ReadStatement*>(stmt)) {
        auto read = dynamic_cast<ReadStatement*>(stmt);
        std::cout << "READ (" << read->varName << ")";
    } else {
        std::cout << "UNKNOWN";
    }
    
    std::cout << std::endl;
}

void Interpreter::waitForStep() {
    if (stepByStep) {
        std::cout << "[DEBUG] Press Enter to continue...";
        std::string dummy;
        std::getline(std::cin, dummy);
    }
}

void Interpreter::setDebugMode(bool enabled, int level, bool step) {
    debugMode = enabled;
    debugLevel = level;
    stepByStep = step;
}

void Interpreter::interpret(Program* program) {
    debugPrint("Starting program execution", 1);
    debugPrint("Total statements: " + std::to_string(program->statements.size()), 2);
    
    currentStatement = 0;
    for (auto& stmt : program->statements) {
        currentStatement++;
        
        if (debugMode) {
            debugPrintStatement(stmt.get());
            if (debugLevel >= 2) {
                debugPrintVariables();
            }
            waitForStep();
        }
        
        execute(stmt.get());
        
        if (debugMode && debugLevel >= 3) {
            std::cout << "[DEBUG] Statement completed\n";
            debugPrintVariables();
        }
    }
    
    debugPrint("Program execution completed", 1);
    if (debugLevel >= 2) {
        std::cout << "[DEBUG] Final state:\n";
        debugPrintVariables();
    }
}