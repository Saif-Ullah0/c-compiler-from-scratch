#include "lexer/lexer.h"
#include "lexer/keyword_table.h"
#include <cctype>

Lexer::Lexer(const std::string& source)
    : src(source), pos(0), line(1), col(1)
{
}

char Lexer::peek(int offset) const {
    size_t idx = pos + offset;
    if (idx >= src.size()) return '\0';
    return src[idx];
}

bool Lexer::isAtEnd() const {
    return pos >= src.size();
}

char Lexer::advance() {
    if (isAtEnd()) return '\0';
    char c = src[pos];
    pos++;
    if (c == '\n') {
        line++;
        col = 1;
    } else {
        col++;
    }
    return c;
}

void Lexer::skipWhitespace() {
    while (!isAtEnd()) {
        char c = peek();
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
            advance();
        } else {
            break;
        }
    }
}

Token Lexer::scanIdentifierOrKeyword() {
    int startLine = line;
    int startCol  = col;
    std::string buf;

    while (!isAtEnd()) {
        char c = peek();
        if (std::isalpha(static_cast<unsigned char>(c)) ||
            std::isdigit(static_cast<unsigned char>(c)) ||
            c == '_') {
            buf += advance();
        } else {
            break;
        }
    }

    if (isKeyword(buf)) {
        return Token{TokenType::KEYWORD, buf, startLine, startCol};
    } else {
        return Token{TokenType::IDENTIFIER, buf, startLine, startCol};
    }
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (!isAtEnd()) {
        skipWhitespace();
        if (isAtEnd()) break;

        char c = peek();

        if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
            tokens.push_back(scanIdentifierOrKeyword());
        } else {
            // Phase 1: ignore numbers, strings, symbols, operators.
            // Later phases will replace this else-branch with real scanners.
            advance();
        }
    }

    tokens.push_back(Token{TokenType::END_OF_FILE, "", line, col});
    return tokens;
}