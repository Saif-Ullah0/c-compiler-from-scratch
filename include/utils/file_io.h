#pragma once
#include <string>
#include <vector>
#include "common/token.h"

std::string readFile(const std::string& path);

void writeTokens(const std::string& path, const std::vector<Token>& tokens);

std::string tokenTypeToString(TokenType type);