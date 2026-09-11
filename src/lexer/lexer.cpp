#include "lexer/lexer.h"
#include "lexer/keyword_table.h"
#include <cctype>
#include <iostream>

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
        }
        else if (std::isdigit(static_cast<unsigned char>(c)) ||
                 (c == '.' && std::isdigit(static_cast<unsigned char>(peek(1))))) {
            tokens.push_back(scanNumber());
        }
        else if (c == '"') {
            tokens.push_back(scanString());
        }
        else if (c == '\'') {
            tokens.push_back(scanChar());
        }
        else {
            // Phase 4 will handle operators/separators
            advance();
        }
    }

    tokens.push_back(Token{TokenType::END_OF_FILE, "", line, col});
    return tokens;
}

bool Lexer::isHexDigit(char c) const {
    return std::isdigit(static_cast<unsigned char>(c)) ||
           (c >= 'a' && c <= 'f') ||
           (c >= 'A' && c <= 'F');
}

Token Lexer::scanNumber() {
    int startLine = line;
    int startCol  = col;
    std::string buf;
    bool isFloat = false;

    // ---- Hex path: 0x or 0X ----
    if (peek() == '0' && (peek(1) == 'x' || peek(1) == 'X')) {
        buf += advance();          // '0'
        buf += advance();          // 'x' / 'X'
        while (isHexDigit(peek())) {
            buf += advance();
        }
        return Token{TokenType::INT_CONST, buf, startLine, startCol};
    }

    // ---- Consume integer digits ----
    while (std::isdigit(static_cast<unsigned char>(peek()))) {
        buf += advance();
    }

    // ---- Dot -> becomes float ----
    if (peek() == '.') {
        isFloat = true;
        buf += advance();
        while (std::isdigit(static_cast<unsigned char>(peek()))) {
            buf += advance();
        }
    }

    // ---- Exponent: e or E ----
    if (peek() == 'e' || peek() == 'E') {
        isFloat = true;
        buf += advance();
        if (peek() == '+' || peek() == '-') {
            buf += advance();
        }
        while (std::isdigit(static_cast<unsigned char>(peek()))) {
            buf += advance();
        }
    }

    // ---- Classify ----
    if (isFloat) {
        return Token{TokenType::FLOAT_CONST, buf, startLine, startCol};
    }
    return Token{TokenType::INT_CONST, buf, startLine, startCol};
}

Token Lexer::scanString() {
    int startLine = line;
    int startCol  = col;
    std::string buf;

    buf += advance();          // consume opening "

    while (!isAtEnd() && peek() != '"') {
        if (peek() == '\\') {
            buf += advance();          // consume backslash
            if (!isAtEnd()) {
                buf += advance();      // consume escaped char
            }
        } else {
            buf += advance();
        }
    }

    if (!isAtEnd() && peek() == '"') {
        buf += advance();      // consume closing "
    } 
    else {
        std::cerr << "Warning: unterminated string at line "
                  << startLine << "\n";
    }
    

    return Token{TokenType::STRING_LITERAL, buf, startLine, startCol};
}

Token Lexer::scanChar() {
    int startLine = line;
    int startCol  = col;
    std::string buf;

    buf += advance();          // opening '

    while (!isAtEnd() && peek() != '\'') {
        if (peek() == '\\') {
            buf += advance();          // backslash
            if (!isAtEnd()) {
                buf += advance();      // escaped char
            }
        } else {
            buf += advance();
        }
    }

    if (!isAtEnd() && peek() == '\'') {
        buf += advance();      // closing '
    } else {
        std::cerr << "Warning: unterminated char at line "
                  << startLine << "\n";
    }

    return Token{TokenType::CHAR_CONST, buf, startLine, startCol};
}