#include <iostream>
#include <cstring>
#include <fstream>
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Interpreter.hpp"

int main(int argc, char** argv) {
    if (!argc) {
        exit(0);
    }
    bool verboseMode = false;
    size_t numberOfArguments = 0;

    size_t j = 1;
    while (argv[j]) {
        if (strcmp(argv[j], "-verbose") == 0) {
            verboseMode = true;
        } else {
            numberOfArguments++;
        }
        j++;
    }

    Lexer *lexer = new Lexer();
    Parser *parser = new Parser();
    Interpreter *interpreter = new Interpreter(verboseMode);
    std::string inputLine;

    if (numberOfArguments == 0) {
        printf("=============== START ===============\n");

        while (std::getline(std::cin, inputLine)) {
            if (inputLine.length() == 2 && inputLine == ";;") {
                break ;
            }
            lexer->analyseInputLine(inputLine);
        }
    } else if (numberOfArguments == 1) {
        std::ifstream file(argv[1]);

        if (file.is_open()) {
            while (std::getline(file, inputLine)) {
                lexer->analyseInputLine(inputLine);
            }
        } else {
            std::cout << "Unable to open file" << std::endl;
            exit(1);
        }
    } else {
        std::cout << "Usage: './abstractVM' OR './abstractVM filename'" << std::endl;
        exit(1);
    }

//    std::cout << "=============== PARSED LINES ===============" << std::endl;
//    for (ssize_t i = 0; i < parser->getParsedLines().size(); i++) {
//        std::cout << parser->getParsedLines()[i].instruction << " " << parser->getParsedLines()[i].type << " " << parser->getParsedLines()[i].value << std::endl;
//    }
    std::cout << "=============== LEXER ERRORS ===============" << std::endl;
    for (unsigned long i = 0; i < lexer->getErrors().size(); i++) {
        std::cout << lexer->getErrors()[i] << std::endl;
    }
    std::cout << "===============+++++++++++++++===============" << std::endl;

    for (unsigned long i = 0; i < lexer->getInput().size(); i++) {
//        std::cout << lexer->getInput()[i].instruction << std::endl;
        parser->parseInputLine(lexer->getInput()[i]);
    }
    parser->checkForExitCommand();

    std::cout << "=============== PARSER ERRORS ===============" << std::endl;
    for (unsigned long i = 0; i < parser->getParserErrors().size(); i++) {
        std::cout << parser->getParserErrors()[i] << std::endl;
    }
    std::cout << "===============+++++++++++++++===============" << std::endl;

    if (lexer->getErrors().size() || parser->getParserErrors().size()) {
        std::cout << "Exiting..." << std::endl;
        exit(1);
    } else {
        std::cout << "=============== EXECUTING COMMANDS ===============" << std::endl;
    }

    for (unsigned long i = 0; i < parser->getParsedLines().size(); i++) {
        interpreter->executeCommand(parser->getParsedLines()[i]);
    }

    std::cout << "=============== EXECUTION FINISHED ===============" << std::endl;

    return 0;
}
