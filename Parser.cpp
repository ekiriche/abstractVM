//
// Created by The Champ on 2/6/2020.
//

#include "Parser.hpp"

Parser::Parser() {

}

Parser::~Parser() {

}

Parser::Parser(Parser const &parser) {
    *this = parser;
};

Parser& Parser::operator=(Parser const &parser) {
    if (this != &parser) {
        this->_parserErrors = parser._parserErrors;
        this->_parsedLines = parser._parsedLines;
    }
    return *this;
}

void Parser::parseInputLine(INPUT_LINE &line) {
    PARSED_LINE parsedLine = {};

    if (line.instruction == "push" || line.instruction == "pop" || line.instruction == "dump" ||
    line.instruction == "assert" || line.instruction == "add" || line.instruction == "sub" ||
    line.instruction == "mul" || line.instruction == "div" || line.instruction == "mod" ||
    line.instruction == "print" || line.instruction == "exit") {
        if ((line.instruction == "push" || line.instruction == "assert") && line.value.empty()) {
            this->_parserErrors.push_back("Parser error: instruction " + line.instruction +
            " requires a second parameter as value");
            return ;
        }

        parsedLine.instruction = line.instruction;
    } else {
        this->_parserErrors.push_back("Parser error: undefined instruction at line " +
        std::to_string(this->_parsedLines.size() + 1));
        return ;
    }

    if (!line.value.empty()) {
        if (!line.value.find('(') || line.value.find(')') != line.value.length() - 1) {
            this->_parserErrors.push_back("Parser error: second parameter at line " +
            std::to_string(this->_parsedLines.size() + 1) + " is invalid");
            return ;
        }

        std::string valueType = line.value.substr(0, line.value.find('c') - 1);
        if (valueType == "int8") {
            parsedLine.type = Int8;
        } else if (valueType == "int16") {
            parsedLine.type = Int16;
        } else if (valueType == "int32") {
            parsedLine.type = Int32;
        } else if (valueType == "float") {
            parsedLine.type = Float;
        } else if (valueType == "double") {
            parsedLine.type = Double;
        } else {
            this->_parserErrors.push_back("Parser error: unrecognized value type at line " +
            std::to_string(this->_parsedLines.size() + 1));
            return ;
        }

        std::string value = line.value.substr(line.value.find('(') + 1,
                line.value.length() - line.value.find('(') - 2);

        bool dotFound = false;
        for (int i = 0; i < value.length(); i++) {
            if (value[i] == '.' && !dotFound && i != 0 && i != value.length() - 1) {
                dotFound = true;
            } else if ((value[i] == '-' && i != 0) || (value[i] == '.' && dotFound) ||
            (!isdigit(value[i]) && value[i] != '-' && value[i] != '.')) {
                this->_parserErrors.push_back("Parser error: invalid value at line" +
                std::to_string(this->_parsedLines.size() + 1));
                return ;
            }
        }

        parsedLine.value = value;
        parsedLine.comment = line.comment;
    }
}




