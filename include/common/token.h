#pragma once
#include <string>

enum class TokenType {
	KEYWORD,
	IDENTIFIER,
	INT_CONST,
	FLOAT_CONST,
	CHAR_CONST,
	STRING_LITERAL,
	OPERATOR,
	SEPARATOR,
	PREPROCESSOR,
	COMMENT,
	UNKNOWN,
	END_OF_FILE
};

struct Token {
	TokenType type;
	std::string lexeme;
	int line;
	int column;
};

std::string tokenTypeToString(TokenType t);
