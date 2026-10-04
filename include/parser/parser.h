#pragma once
#include "common/token.h"
#include <vector>
#include <string>

class Parser {
public:
    Parser(const std::vector<Token>& tokens)
        : tokens(tokens), currentIndex(0) {}

    void parse();

private:
    const std::vector<Token>& tokens;
    size_t currentIndex;

    Token       current() const;
    Token       peek(int offset = 0) const;
    std::string peekLexeme() const;
    void        advance();
    bool        match(TokenType type);
    bool        matchLexeme(const std::string& lexeme);
    void        error(const std::string& message) const;

    void parseProgram();
    void parseST_LIST();
    void parseST();
    void parseSST();
    void parseCST();
    void parseAGAR();
    void parseMAGAR();      // ← renamed
    void parseJAB();
    void parseAS();
    void parseBRK();
    void parseE();
    void parseEdash();
    void parseT();
    void parseC();
};