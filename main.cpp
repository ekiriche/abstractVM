#include <iostream>
#include "Lexer.hpp"

int main(int argc, char** argv) {
    if (argc > 2) {
        printf("Usage: ./aVM\n"
               "       ./aVM [filename]\n");
        exit(0);
    }

    Lexer *lexer = new Lexer();

    if (argc == 1) {
        printf("=============== START ===============\n");
        std::string input;

        while (!lexer->getEndOfInputDetected()) {
            if (std::getline(std::cin, input)) {
                if (input.length() >= 2 && input.substr(0, 2) == ";;") {
                    break ;
                }
                lexer->analyseInputLine(input);
            }
        }


    }

    return 0;
}
