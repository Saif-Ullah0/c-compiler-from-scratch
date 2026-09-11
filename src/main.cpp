#include "lexer/lexer.h"
#include "utils/file_io.h"
#include <iostream>
#include <exception>

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0]
                  << " lex <input.c> <output.txt>\n";
        return 1;
    }

    std::string mode = argv[1];
    if (mode != "lex") {
        std::cerr << "Error: unsupported mode '" << mode
                  << "'. Phase 1 supports only 'lex'.\n";
        return 1;
    }

    std::string inputPath  = argv[2];
    std::string outputPath = argv[3];

    try {
        std::string source = readFile(inputPath);

        Lexer lexer(source);
        std::vector<Token> tokens = lexer.tokenize();

        writeTokens(outputPath, tokens);

        std::cout << "OK: " << tokens.size()
                  << " tokens written to " << outputPath << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}