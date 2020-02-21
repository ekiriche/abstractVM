#include <iostream>
#include "Lexer.hpp"
//#include "Parser.cpp"
//#include "Factory.hpp"
#include "eOperand.hpp"
#include "IOperand.hpp"

int main(int argc, char** argv) {
    if (argc > 2) {
        printf("Usage: ./aVM\n"
               "       ./aVM [filename]\n");
        exit(0);
    }

    Lexer *lexer = new Lexer();
//    eOperand<int8_t> *some = new eOperand<int8_t>(Int8, "200");
    eOperand<int8_t> *some1 = (eOperand<int8_t> *) Factory().createOperand(Int8, "40");
    eOperand<int8_t> *some2 = (eOperand<int8_t> *) Factory().createOperand(Int8, "60");
    eOperand<int8_t> *some3 = (eOperand<int8_t> *) (*some1 + *some2);
    some3 = (eOperand<int8_t> *) (*some3 % *some1);
    std::cout << std::to_string(some3->getValue()) << std::endl;

    if (argc == 1) {
        printf("=============== START ===============\n");
        std::string input;

        while (true) {
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
