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
        log("[match type] " + tokens[currentIndex].lexeme);
        advance();
        return true;
    }
    error("expected token type");
    return false;
}

bool Parser::matchLexeme(const std::string& lexeme) {
    if (tokens[currentIndex].lexeme == lexeme) {
        log("[match] " + lexeme);
        advance();
        return true;
    }
    error("expected '" + lexeme + "'");
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
    std::cout << "Parse successful ,,,\n";
}

// ───────────── Parse Functions ─────────────

void Parser::parseProgram() {
    log("parseProgram"); indent++;
    matchLexeme("main");
    matchLexeme("shro");
    parseST_LIST();
    matchLexeme("khatam");
    indent--;
}

void Parser::parseST_LIST() {
    TokenType t = current().type;
    std::string lex = current().lexeme;
    bool startsStmt =
        (t == TokenType::KEYWORD &&
         (lex == "agar" || lex == "jabtak" || lex == "nikal" || lex == "shro")) ||
        (t == TokenType::IDENTIFIER);
    if (startsStmt) {
        log("parseST_LIST"); indent++;
        parseST();
        parseST_LIST();
        indent--;
    }
    // else: ε — silent
}

void Parser::parseST() {
    log("parseST"); indent++;
    if (current().lexeme == "shro") parseCST();
    else                             parseSST();
    indent--;
}

void Parser::parseSST() {
    log("parseSST"); indent++;
    std::string lex = current().lexeme;
    if (lex == "agar")        parseAGAR();
    else if (lex == "jabtak") parseJAB();
    else if (lex == "nikal")  parseBRK();
    else if (current().type == TokenType::IDENTIFIER) parseAS();
    else error("expected statement");
    indent--;
}

void Parser::parseCST() {
    log("parseCST"); indent++;
    matchLexeme("shro");
    parseST_LIST();
    matchLexeme("khatam");
    indent--;
}

void Parser::parseAGAR() {
    log("parseAGAR"); indent++;
    matchLexeme("agar");
    matchLexeme("(");
    parseE();
    matchLexeme(")");
    matchLexeme("shro");
    parseST_LIST();
    matchLexeme("khatam");
    parseMAGAR();
    indent--;
}

void Parser::parseMAGAR() {
    if (current().lexeme == "magar") {
        log("parseMAGAR"); indent++;
        advance();
        matchLexeme("shro");
        parseST_LIST();
        matchLexeme("khatam");
        indent--;
    }
    // else: ε — silent
}

void Parser::parseJAB() {
    log("parseJAB"); indent++;
    matchLexeme("jabtak");
    matchLexeme("(");
    parseE();
    matchLexeme(")");
    matchLexeme("shro");
    parseST_LIST();
    matchLexeme("khatam");
    indent--;
}

void Parser::parseAS() {
    log("parseAS"); indent++;
    if (current().type != TokenType::IDENTIFIER)
        error("expected identifier");
    log("[match id] " + current().lexeme);
    advance();
    matchLexeme("medalo");
    parseE();
    matchLexeme(";");
    indent--;
}

void Parser::parseBRK() {
    log("parseBRK"); indent++;
    matchLexeme("nikal");
    matchLexeme(";");
    indent--;
}

void Parser::parseE() {
    log("parseE"); indent++;
    parseT();
    parseEdash();
    indent--;
}
void Parser::parseEdash() {
    std::string lex = current().lexeme;
    bool isOp = (lex == "+" || lex == "-" || lex == "*" || lex == "/" ||
                 lex == "==" || lex == "!=" || lex == "chota" || lex == "bara");
    if (isOp) {
        log("parseEdash"); indent++;
        log("[match op] " + lex);    // ← NEW LINE
        advance();
        parseT();
        parseEdash();
        indent--;
    }
}

void Parser::parseT() {
    log("parseT"); indent++;
    TokenType t = current().type;
    if (t == TokenType::IDENTIFIER) {
        log("[match id] " + current().lexeme);
        advance();
    } else if (t == TokenType::INT_CONST || t == TokenType::FLOAT_CONST) {
        log("[match num] " + current().lexeme);
        advance();
    } else if (current().lexeme == "(") {
        matchLexeme("(");
        parseE();
        matchLexeme(")");
    } else {
        error("expected ID, number, or (");
    }
    indent--;
}

void Parser::parseC() {
    // Same as T
}

void Parser::log(const std::string& msg) const {
    for (int k = 0; k < indent; ++k) {
        std::cout << "    ";
    }
    std::cout << msg << "\n";
}