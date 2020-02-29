//
// Created by The Champ on 1/29/2020.
//
#include <iostream>
#include "Lexer.hpp"
#include <algorithm>

Lexer::Lexer() {
};

Lexer::~Lexer() {

};

Lexer::Lexer(Lexer const &lexer) {
    *this = lexer;
};

Lexer& Lexer::operator=(Lexer const &lexer) {
    if (this != &lexer) {
        this->_input = lexer._input;
        this->_errors = lexer._errors;
    }
    return *this;
}

void Lexer::analyseInputLine(std::string &line) {
    INPUT_LINE tokens = {};

    line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](int ch) {
        return !std::isspace(ch);
    }));

    line.erase(std::find_if(line.rbegin(), line.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), line.end());

    if (line.length()) {
        if (line[0] == ';') {
            tokens.comment = line.substr(1);
        } else {
            int i = 0;
            while (i < line.length() && !isspace(line[i]) && line[i] != ';') {
                i++;
            }
            tokens.instruction = line.substr(0, i);

            if (i != line.length()) {
                while (i < line.length() && isspace(line[i])) {
                    i++;
                }

                if (line[i] == ';') {
                    tokens.comment = line.substr(i + 1);
                } else {
                    int start = i;
                    while (i < line.length() && !isspace(line[i]) && line[i] != ';') {
                        i++;
                    }
                    tokens.value = line.substr(start, i - start);

                    if (i != line.length()) {
                        while (i < line.length() && isspace(line[i])) {
                            i++;
                        }
                        if (line[i] != ';') {
                            this->_errors.push_back("Lexer error: undefined token at " +
                            std::to_string(this->_input.size() + 1) + ":" + std::to_string(i));
                            return ;
                        } else {
                            tokens.comment = line.substr(i + 1);
                        }
                    }
                }
            }
        }
        this->_input.push_back(tokens);
    }
}

std::vector<INPUT_LINE> Lexer::getInput() {
    return this->_input;
}

std::vector<std::string> Lexer::getErrors() {
    return this->_errors;
}


