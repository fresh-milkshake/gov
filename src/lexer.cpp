#include "lexer.h"
#include <iostream>

Lexer::Lexer(const std::string& source) : source(source), current(0), line(1), column(1) {
    initKeywords();
}

void Lexer::initKeywords() {
    keywords["!I_LOVE_GOVERNMENT"] = TokenType::I_LOVE_GOVERNMENT;
    keywords["PRAISE_LEADER"] = TokenType::PRAISE_LEADER;
    keywords["OBEY_PARTY_LINE"] = TokenType::OBEY_PARTY_LINE;
    keywords["PLEASE"] = TokenType::PLEASE;
    keywords["DECLARE_VARIABLE"] = TokenType::DECLARE_VARIABLE;
    keywords["AS"] = TokenType::AS;
    keywords["INTEGER"] = TokenType::INTEGER_TYPE;
    keywords["STRING"] = TokenType::STRING_TYPE;
    keywords["ARRAY_OF_STRING"] = TokenType::ARRAY_OF_STRING;
    keywords["SIZE"] = TokenType::SIZE;
    keywords["SET"] = TokenType::SET;
    keywords["TO"] = TokenType::TO;
    keywords["FOR_THE_PEOPLE"] = TokenType::FOR_THE_PEOPLE;
    keywords["LESS_THAN"] = TokenType::LESS_THAN;
    keywords["DO"] = TokenType::DO;
    keywords["END_FOR_THE_PEOPLE"] = TokenType::END_FOR_THE_PEOPLE;
    keywords["INCREMENT"] = TokenType::INCREMENT;
    keywords["BY"] = TokenType::BY;
    keywords["DENOUNCE_IMPERIALIST_ERRORS"] = TokenType::DENOUNCE_IMPERIALIST_ERRORS;
    keywords["WHILE"] = TokenType::WHILE;
    keywords["EQUALS"] = TokenType::EQUALS;
    keywords["AND"] = TokenType::AND;
    keywords["OR"] = TokenType::OR;
    keywords["NOT_EQUALS"] = TokenType::NOT_EQUALS;
    keywords["IF"] = TokenType::IF;
    keywords["THEN"] = TokenType::THEN;
    keywords["ELSE"] = TokenType::ELSE;
    keywords["ELSE_IF"] = TokenType::ELSE_IF;
    keywords["END_IF"] = TokenType::END_IF;
    keywords["END_WHILE"] = TokenType::END_WHILE;
    keywords["READ"] = TokenType::READ;
}

char Lexer::advance() {
    if (isAtEnd()) return '\0';
    column++;
    return source[current++];
}

char Lexer::peek() {
    if (isAtEnd()) return '\0';
    return source[current];
}

char Lexer::peekNext() {
    if (current + 1 >= source.length()) return '\0';
    return source[current + 1];
}

bool Lexer::isAtEnd() {
    return current >= source.length();
}

bool Lexer::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || c == '!';
}

bool Lexer::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Lexer::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

Token Lexer::makeToken(TokenType type, const std::string& value) {
    return {type, value, line, column};
}

Token Lexer::string() {
    std::string value = "";
    
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') {
            line++;
            column = 0;
        }
        value += advance();
    }
    
    if (isAtEnd()) {
        std::cerr << "Unterminated string at line " << line << std::endl;
        return makeToken(TokenType::EOF_TOKEN);
    }
    
    advance(); // closing quote
    return makeToken(TokenType::STRING, value);
}

Token Lexer::number() {
    std::string value = "";
    
    while (isDigit(peek())) {
        value += advance();
    }
    
    return makeToken(TokenType::INTEGER, value);
}

Token Lexer::identifier() {
    std::string value = "";
    
    while (isAlphaNumeric(peek())) {
        value += advance();
    }
    
    auto it = keywords.find(value);
    if (it != keywords.end()) {
        return makeToken(it->second, value);
    }
    
    return makeToken(TokenType::IDENTIFIER, value);
}

void Lexer::skipWhitespace() {
    while (true) {
        char c = peek();
        if (c == ' ' || c == '\r' || c == '\t') {
            advance();
        } else if (c == '/' && peekNext() == '/') {
            // Skip comment
            while (peek() != '\n' && !isAtEnd()) advance();
        } else {
            break;
        }
    }
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    
    while (!isAtEnd()) {
        skipWhitespace();
        
        if (isAtEnd()) break;
        
        char c = advance();
        
        switch (c) {
            case '\n':
                line++;
                column = 1;
                tokens.push_back(makeToken(TokenType::NEWLINE));
                break;
            case '"':
                tokens.push_back(string());
                break;
            case '[':
                tokens.push_back(makeToken(TokenType::LEFT_BRACKET));
                break;
            case ']':
                tokens.push_back(makeToken(TokenType::RIGHT_BRACKET));
                break;
            case '(':
                tokens.push_back(makeToken(TokenType::LEFT_PAREN));
                break;
            case ')':
                tokens.push_back(makeToken(TokenType::RIGHT_PAREN));
                break;
            case '+':
                tokens.push_back(makeToken(TokenType::PLUS));
                break;
            case '-':
                tokens.push_back(makeToken(TokenType::MINUS));
                break;
            case '*':
                tokens.push_back(makeToken(TokenType::MULTIPLY));
                break;
            case '/':
                tokens.push_back(makeToken(TokenType::DIVIDE));
                break;
            default:
                if (isDigit(c)) {
                    current--; // Back up
                    column--;
                    tokens.push_back(number());
                } else if (isAlpha(c)) {
                    current--; // Back up
                    column--;
                    tokens.push_back(identifier());
                } else {
                    std::cerr << "Unexpected character '" << c << "' at line " << line << std::endl;
                }
                break;
        }
    }
    
    tokens.push_back(makeToken(TokenType::EOF_TOKEN));
    return tokens;
}