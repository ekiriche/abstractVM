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

private:
    std::vector<INPUT_LINE> _parsedLines;
    std::vector<std::string> _parserErrors;
};


#endif //AVM_PARSER_HPP
