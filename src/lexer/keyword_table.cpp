#include "lexer/keyword_table.h"
#include <vector>
#include <string>

static const std::vector<std::string> KEYWORDS = {
    "int", "char", "float", "double", "void", "short", "long",
    "int16", "int32", "uint16", "uint32", "char", "float", "real",
    "signed", "unsigned", "_Bool",
    "if", "else", "for", "while", "do", "switch", "case",
    "default", "break", "continue", "return", "goto",
    "sizeof", "typedef", "struct", "union", "enum",
    "static", "extern", "register", "volatile", "auto", "const",
    "main", "agar", "magar", "jabtak", "shro", "khatam", "nikal", "medalo",
    "chota", "bara"
};

bool isKeyword(const std::string& word) {
    for (const auto& kw : KEYWORDS) {
        if (kw == word) return true;
    }
    return false;
}

