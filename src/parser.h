#pragma once
#include "lexer.h"
#include <memory>
#include <variant>

// AST Node types
struct ASTNode {
    virtual ~ASTNode() = default;
};

struct Expression : ASTNode {
    virtual ~Expression() = default;
};

struct Statement : ASTNode {
    virtual ~Statement() = default;
};

// Expressions
struct StringLiteral : Expression {
    std::string value;
    StringLiteral(const std::string& val) : value(val) {}
};

struct IntegerLiteral : Expression {
    int value;
    IntegerLiteral(int val) : value(val) {}
};

struct Identifier : Expression {
    std::string name;
    Identifier(const std::string& n) : name(n) {}
};

struct ArrayAccess : Expression {
    std::unique_ptr<Expression> array;
    std::unique_ptr<Expression> index;
    ArrayAccess(std::unique_ptr<Expression> arr, std::unique_ptr<Expression> idx) 
        : array(std::move(arr)), index(std::move(idx)) {}
};

struct BinaryOp : Expression {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
    TokenType op;
    BinaryOp(std::unique_ptr<Expression> l, TokenType o, std::unique_ptr<Expression> r)
        : left(std::move(l)), op(o), right(std::move(r)) {}
};

// Statements
struct PrintStatement : Statement {
    std::unique_ptr<Expression> expr;
    PrintStatement(std::unique_ptr<Expression> e) : expr(std::move(e)) {}
};

struct VarDeclaration : Statement {
    std::string name;
    std::string type;
    int arraySize;
    VarDeclaration(const std::string& n, const std::string& t, int size = 0) 
        : name(n), type(t), arraySize(size) {}
};

struct Assignment : Statement {
    std::string varName;
    std::unique_ptr<Expression> index; // for array assignment
    std::unique_ptr<Expression> value;
    Assignment(const std::string& name, std::unique_ptr<Expression> val, std::unique_ptr<Expression> idx = nullptr)
        : varName(name), value(std::move(val)), index(std::move(idx)) {}
};

struct ForLoop : Statement {
    std::string varName;
    std::unique_ptr<Expression> condition;
    std::vector<std::unique_ptr<Statement>> body;
    ForLoop(const std::string& var, std::unique_ptr<Expression> cond)
        : varName(var), condition(std::move(cond)) {}
};

struct WhileLoop : Statement {
    std::unique_ptr<Expression> condition;
    std::vector<std::unique_ptr<Statement>> body;
    WhileLoop(std::unique_ptr<Expression> cond) : condition(std::move(cond)) {}
};

struct ElseIfClause {
    std::unique_ptr<Expression> condition;
    std::vector<std::unique_ptr<Statement>> body;
    ElseIfClause(std::unique_ptr<Expression> cond) : condition(std::move(cond)) {}
};

struct IfStatement : Statement {
    std::unique_ptr<Expression> condition;
    std::vector<std::unique_ptr<Statement>> thenBranch;
    std::vector<ElseIfClause> elseIfClauses;
    std::vector<std::unique_ptr<Statement>> elseBranch;
    IfStatement(std::unique_ptr<Expression> cond) : condition(std::move(cond)) {}
};

struct IncrementStatement : Statement {
    std::string varName;
    int amount;
    IncrementStatement(const std::string& name, int amt) : varName(name), amount(amt) {}
};

struct ReadStatement : Statement {
    std::string varName;
    ReadStatement(const std::string& name) : varName(name) {}
};

struct Program : ASTNode {
    std::vector<std::unique_ptr<Statement>> statements;
};

class Parser {
private:
    std::vector<Token> tokens;
    size_t current;
    
    Token peek();
    Token previous();
    bool isAtEnd();
    bool check(TokenType type);
    bool match(std::initializer_list<TokenType> types);
    Token advance();
    Token consume(TokenType type, const std::string& message);
    void skipNewlines();
    
    std::unique_ptr<Expression> expression();
    std::unique_ptr<Expression> logicalOr();
    std::unique_ptr<Expression> logicalAnd();
    std::unique_ptr<Expression> equality();
    std::unique_ptr<Expression> addition();
    std::unique_ptr<Expression> multiplication();
    std::unique_ptr<Expression> primary();
    
    std::unique_ptr<Statement> statement();
    std::unique_ptr<Statement> printStatement();
    std::unique_ptr<Statement> varDeclaration();
    std::unique_ptr<Statement> assignment();
    std::unique_ptr<Statement> forLoop();
    std::unique_ptr<Statement> whileLoop();
    std::unique_ptr<Statement> ifStatement();
    std::unique_ptr<Statement> incrementStatement();
    std::unique_ptr<Statement> readStatement();
    
public:
    Parser(std::vector<Token> tokens);
    std::unique_ptr<Program> parse();
};