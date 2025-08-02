#pragma once
#include <string>
#include <vector>
#include <unordered_map>

enum class TokenType {
    // Literals
    STRING,
    INTEGER,
    IDENTIFIER,
    
    // Keywords
    I_LOVE_GOVERNMENT,
    PRAISE_LEADER,
    OBEY_PARTY_LINE,
    PLEASE,
    DECLARE_VARIABLE,
    AS,
    INTEGER_TYPE,
    STRING_TYPE,
    ARRAY_OF_STRING,
    SIZE,
    SET,
    TO,
    FOR_THE_PEOPLE,
    LESS_THAN,
    DO,
    END_FOR_THE_PEOPLE,
    INCREMENT,
    BY,
    DENOUNCE_IMPERIALIST_ERRORS,
    WHILE,
    EQUALS,
    AND,
    OR,
    NOT_EQUALS,
    IF,
    THEN,
    ELSE,
    ELSE_IF,
    END_IF,
    END_WHILE,
    READ,
    
    // Operators
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    
    // Punctuation
    LEFT_BRACKET,
    RIGHT_BRACKET,
    LEFT_PAREN,
    RIGHT_PAREN,
    QUOTE,
    NEWLINE,
    EOF_TOKEN,
    
    // Comments
    COMMENT
};

struct Token {
    TokenType type;
    std::string value;
    int line;
    int column;
};

class Lexer {
private:
    std::string source;
    size_t current;
    int line;
    int column;
    std::unordered_map<std::string, TokenType> keywords;
    
    void initKeywords();
    char advance();
    char peek();
    char peekNext();
    bool isAtEnd();
    bool isAlpha(char c);
    bool isDigit(char c);
    bool isAlphaNumeric(char c);
    Token makeToken(TokenType type, const std::string& value = "");
    Token string();
    Token number();
    Token identifier();
    void skipWhitespace();
    
public:
    Lexer(const std::string& source);
    std::vector<Token> tokenize();
};