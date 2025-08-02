#pragma once
#include "parser.h"
#include <unordered_map>
#include <variant>
#include <vector>

using Value = std::variant<int, std::string, std::vector<std::string>>;

class Interpreter {
private:
    std::unordered_map<std::string, Value> variables;
    bool debugMode = false;
    int debugLevel = 0;
    bool stepByStep = false;
    int currentStatement = 0;
    
    Value evaluate(Expression* expr);
    void execute(Statement* stmt);
    std::string valueToString(const Value& val);
    bool isTruthy(const Value& val);
    Value binaryOperation(const Value& left, TokenType op, const Value& right);
    
    void debugPrint(const std::string& message, int level = 1);
    void debugPrintVariables();
    void debugPrintStatement(Statement* stmt);
    void waitForStep();
    
public:
    void interpret(Program* program);
    void setDebugMode(bool enabled, int level = 1, bool step = false);
};