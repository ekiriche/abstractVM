//
// Created by The Champ on 2/6/2020.
//

#ifndef AVM_PARSER_HPP
#define AVM_PARSER_HPP

#include "Lexer.hpp"
#include <iostream>
#include "IOperand.hpp"


struct PARSED_LINE {
    std::string instruction;
    eOperandType type;
    std::string value;
    std::string comment;
};

class Parser {
public:
    Parser();
    ~Parser();
    Parser(Parser const &parser);
    Parser& operator=(Parser const &parser);

    void parseInputLine(INPUT_LINE &line);
    void checkForExitCommand();

    std::vector<PARSED_LINE> getParsedLines();
    std::vector<std::string> getParserErrors();

private:
    std::vector<PARSED_LINE> _parsedLines;
    std::vector<std::string> _parserErrors;
    unsigned int _currentLine;
};


#endif //AVM_PARSER_HPP
