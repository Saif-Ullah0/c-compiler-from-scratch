#include "utils/file_io.h"
#include <fstream>
#include <iterator>
#include <stdexcept>

std::string readFile(const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open: " + path);
    }
    std::string content((std::istreambuf_iterator<char>(in)),
                         std::istreambuf_iterator<char>());
    return content;
}

void writeTokens(const std::string& path, const std::vector<Token>& tokens) {
    std::ofstream out(path);
    if (!out.is_open()) {
        throw std::runtime_error("Cannot write: " + path);
    }
    for (const auto& t : tokens) {
        out << tokenTypeToString(t.type) << " " << t.lexeme << "\n";
    }
}

std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::KEYWORD:        return "KEYWORD";
        case TokenType::IDENTIFIER:     return "IDENTIFIER";
        case TokenType::INT_CONST:      return "INT_CONST";
        case TokenType::FLOAT_CONST:    return "FLOAT_CONST";
        case TokenType::CHAR_CONST:     return "CHAR_CONST";
        case TokenType::STRING_LITERAL: return "STRING_LITERAL";
        case TokenType::OPERATOR:       return "OPERATOR";
        case TokenType::SEPARATOR:      return "SEPARATOR";
        case TokenType::PREPROCESSOR:   return "PREPROCESSOR";
        case TokenType::COMMENT:        return "COMMENT";
        case TokenType::UNKNOWN:        return "UNKNOWN";
        case TokenType::END_OF_FILE:    return "END_OF_FILE";
        default:                        return "INVALID";
    }
}