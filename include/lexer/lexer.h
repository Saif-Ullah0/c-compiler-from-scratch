#pragma once
#include "common/token.h"
#include <string>
#include <vector>

class Lexer {
public:
    explicit Lexer(const std::string& source);
    std::vector<Token> tokenize();

private:
    std::string src;
    size_t      pos;
    int         line;
    int         col;
    

    char  peek(int offset = 0) const;
    char  advance();
    bool  isAtEnd() const;
    void  skipWhitespace();
    Token scanIdentifierOrKeyword();
    bool isHexDigit(char c) const;
    Token scanNumber();
    Token scanString();
    Token scanChar();
    Token scanOperatorOrSeparator();
};