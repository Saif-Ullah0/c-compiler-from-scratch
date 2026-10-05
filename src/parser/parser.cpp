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

// ───────────── Parse Functions ─────────────

void Parser::parseProgram() {
    matchLexeme("main");
    matchLexeme("shro");
    parseST_LIST();
    matchLexeme("khatam");
}

void Parser::parseST_LIST() {
    TokenType t = current().type;
    std::string lex = current().lexeme;

    bool startsStmt =
        (t == TokenType::KEYWORD &&
         (lex == "agar" || lex == "jabtak" || lex == "nikal" || lex == "shro")) ||
        (t == TokenType::IDENTIFIER);

    if (startsStmt) {
        parseST();
        parseST_LIST();
    }
    // else: ε — stop
}

void Parser::parseST() {
    if (current().lexeme == "shro") {
        parseCST();
    } else {
        parseSST();
    }
}

void Parser::parseSST() {
    std::string lex = current().lexeme;
    if (lex == "agar")        parseAGAR();
    else if (lex == "jabtak") parseJAB();
    else if (lex == "nikal")  parseBRK();
    else if (current().type == TokenType::IDENTIFIER) parseAS();
    else error("expected statement");
}

void Parser::parseCST() {
    matchLexeme("shro");
    parseST_LIST();
    matchLexeme("khatam");
}

void Parser::parseAGAR() {
    matchLexeme("agar");
    matchLexeme("(");
    parseE();
    matchLexeme(")");
    matchLexeme("shro");
    parseST_LIST();
    matchLexeme("khatam");
    parseMAGAR();
}

void Parser::parseMAGAR() {
    if (current().lexeme == "magar") {
        advance();
        matchLexeme("shro");
        parseST_LIST();
        matchLexeme("khatam");
    }
    // else: ε — nothing
}

void Parser::parseJAB() {
    matchLexeme("jabtak");
    matchLexeme("(");
    parseE();
    matchLexeme(")");
    matchLexeme("shro");
    parseST_LIST();
    matchLexeme("khatam");
}

void Parser::parseAS() {
    if (current().type != TokenType::IDENTIFIER)
        error("expected identifier");
    advance();
    matchLexeme("medalo");
    parseE();
    matchLexeme(";");
}

void Parser::parseBRK() {
    matchLexeme("nikal");
    matchLexeme(";");
}

void Parser::parseE() {
    parseT();
    parseEdash();
}

void Parser::parseEdash() {
    std::string lex = current().lexeme;
    bool isOp = (lex == "+" || lex == "-" || lex == "*" || lex == "/" ||
                 lex == "==" || lex == "!=" || lex == "chota" || lex == "bara");

    if (isOp) {
        advance();
        parseT();
        parseEdash();
    }
    // else: ε — stop
}

void Parser::parseT() {
    TokenType t = current().type;
    if (t == TokenType::IDENTIFIER) {
        advance();
    } else if (t == TokenType::INT_CONST || t == TokenType::FLOAT_CONST) {
        advance();
    } else if (current().lexeme == "(") {
        advance();
        parseE();
        matchLexeme(")");
    } else {
        error("expected ID, number, or (");
    }
}

void Parser::parseC() {
    parseT();   // C is same as T in our grammar 
}