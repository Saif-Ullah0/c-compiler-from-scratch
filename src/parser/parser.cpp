#include "parser/parser.h"
#include <iostream>
#include <cstdlib>


Token Parser::current() const {
    return tokens[currentIndex];
}

Token Parser::peek(int offset) const {
    size_t idx = currentIndex + offset;
    if (idx >= tokens.size()) {
        return tokens.back();
    }
    return tokens[idx];
}

std::string Parser::peekLexeme() const {
    return tokens[currentIndex].lexeme;
}

void Parser::advance() {
    if (tokens[currentIndex].type != TokenType::END_OF_FILE) {
        currentIndex++;
    }
}

bool Parser::match(TokenType type) {
    if (tokens[currentIndex].type == type) {
        advance();
        return true;
    }
    return false;
}

bool Parser::matchLexeme(const std::string& lexeme) {
    if (tokens[currentIndex].lexeme == lexeme) {
        advance();
        return true;
    }
    return false;
}

void Parser::error(const std::string& message) const {
    Token t = tokens[currentIndex];
    std::cerr << "Parse error at line " << t.line
              << ", col " << t.column
              << ": " << message
              << " (got '" << t.lexeme << "')\n";
    std::exit(1);
}


void Parser::parse() {
    parseProgram();
    if (tokens[currentIndex].type != TokenType::END_OF_FILE) {
        error("extra tokens after program");
    }
    std::cout << "Parse successful ✅\n";
}


void Parser::parseProgram()   { /* TODO */ }
void Parser::parseST_LIST()   { /* TODO */ }
void Parser::parseST()        { /* TODO */ }
void Parser::parseSST()       { /* TODO */ }
void Parser::parseCST()       { /* TODO */ }
void Parser::parseAGAR()      { /* TODO */ }
void Parser::parseMAGAR()     { /* TODO */ }
void Parser::parseJAB()       { /* TODO */ }
void Parser::parseAS()        { /* TODO */ }
void Parser::parseBRK()       { /* TODO */ }
void Parser::parseE()         { /* TODO */ }
void Parser::parseEdash()     { /* TODO */ }
void Parser::parseT()         { /* TODO */ }
void Parser::parseC()         { /* TODO */ }