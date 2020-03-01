//
// Created by The Champ on 2/6/2020.
//

#include "Parser.hpp"

Parser::Parser() {
    this->_currentLine = 0;
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
        this->_currentLine = parser._currentLine;
    }
    return *this;
}

void Parser::parseInputLine(INPUT_LINE &line) {
    PARSED_LINE parsedLine = {};

    this->_currentLine++;

    if (line.instruction.empty() && line.value.empty()) {
        parsedLine.comment = line.comment;
        this->_parsedLines.push_back(parsedLine);
        return ;
    }

    if (line.instruction == "push" || line.instruction == "pop" || line.instruction == "dump" ||
    line.instruction == "assert" || line.instruction == "add" || line.instruction == "sub" ||
    line.instruction == "mul" || line.instruction == "div" || line.instruction == "mod" ||
    line.instruction == "print" || line.instruction == "exit" || line.instruction == "max" ||
    line.instruction == "min" || line.instruction == "avg") {
        if ((line.instruction == "push" || line.instruction == "assert") && line.value.empty()) {
            this->_parserErrors.push_back("Parser error: instruction " + line.instruction +
            " requires a second parameter as value");
            return ;
        }

        if (line.instruction != "push" && line.instruction != "assert" && !line.value.empty()) {
            this->_parserErrors.push_back("Parser error: instruction " + line.instruction +
                                          " don't requires a second parameter");
            return ;
        }

        parsedLine.instruction = line.instruction;
    } else {
        this->_parserErrors.push_back("Parser error: undefined instruction at line " +
        std::to_string(this->_currentLine));
        return ;
    }

    if (!line.value.empty()) {
        if (line.instruction != "push" && line.instruction != "assert") {
            this->_parserErrors.push_back("Parser error: no value provided at line " +
                                          std::to_string(this->_currentLine));
            return ;
        }

        if (!line.value.find('(') || line.value.find(')') != line.value.length() - 1) {
            this->_parserErrors.push_back("Parser error: second parameter at line " +
            std::to_string(this->_currentLine) + " is invalid");
            return ;
        }

        std::string valueType = line.value.substr(0, line.value.find('('));

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
            std::to_string(this->_currentLine));
            return ;
        }

        std::string value = line.value.substr(line.value.find('(') + 1,
                line.value.length() - line.value.find('(') - 2);

        if (!value.length()) {
            this->_parserErrors.push_back("Parser error: empty value provided at line " +
                                          std::to_string(this->_currentLine));
            return ;
        }

        bool dotFound = false;
        bool numberFound = false;
        for (unsigned int i = 0; i < value.length(); i++) {
            if (isdigit(value[i])) numberFound = true;

            if (value[i] == '.' && !dotFound && i != 0 && i != value.length() - 1 && numberFound) {
                dotFound = true;
            } else if ((value[i] == '-' && i != 0) || (value[i] == '.' && dotFound) ||
            (!isdigit(value[i]) && value[i] != '-' && value[i] != '.') || (value[i] == '.' && i == value.length() - 1) ||
                    (value[i] == '.' && !numberFound)) {
                this->_parserErrors.push_back("Parser error: invalid value at line " +
                std::to_string(this->_currentLine));
                return ;
            }
        }

        parsedLine.value = value;
        parsedLine.comment = line.comment;
    }

    this->_parsedLines.push_back(parsedLine);
}

void Parser::checkForExitCommand() {
    for (unsigned int i = 0; i < this->_parsedLines.size(); i++) {
        if (this->_parsedLines[i].instruction == "exit") {
            return ;
        }
    }

    this->_parserErrors.push_back("Parser error: no exit instruction");
}

std::vector<PARSED_LINE> Parser::getParsedLines() {
    return this->_parsedLines;
}

std::vector<std::string> Parser::getParserErrors() {
    return this->_parserErrors;
}




