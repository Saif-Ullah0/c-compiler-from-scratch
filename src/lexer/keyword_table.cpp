#include "lexer/keyword_table.h"
#include <vector>
#include <string>

static const std::vector<std::string> KEYWORDS = {
    "int", "char", "float", "double", "void", "short", "long",
    "signed", "unsigned", "_Bool",
    "if", "else", "for", "while", "do", "switch", "case",
    "default", "break", "continue", "return", "goto",
    "sizeof", "typedef", "struct", "union", "enum",
    "static", "extern", "register", "volatile", "auto", "const"
};

bool isKeyword(const std::string& word) {
    for (const auto& kw : KEYWORDS) {
        if (kw == word) return true;
    }
    return false;
}

