//
// Created by The Champ on 1/29/2020.
//
#include <iostream>
#include "Lexer.hpp"
//#include "Functions.cpp"
#include <algorithm>

Lexer::Lexer() {
    this->_endOfInputDetected = false;
};

Lexer::~Lexer() {
//    delete(this->_input);
};

Lexer::Lexer(Lexer const &lexer) {
    *this = lexer;
    this->_input = lexer._input;
    this->_endOfInputDetected = lexer._endOfInputDetected;
};

Lexer& Lexer::operator=(Lexer const &lexer) {
    *this = lexer;
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
//            std::cout << tokens.instruction << std::endl;
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
                    std::cout << i << " " << start << std::endl;
                    tokens.value = line.substr(start, i - start);

                    if (i != line.length()) {
                        while (i < line.length() && isspace(line[i])) {
                            i++;
                        }
                        if (line[i] != ';') {
                            std::cout << "EXCEPTION" << std::endl;
                            //exception should be raised at this line because of unknown token
                        } else {
                            tokens.comment = line.substr(i + 1);
                        }
                    }
                }
            }
        }

        std::cout << tokens.instruction << " | " << tokens.value << " | " << tokens.comment << std::endl;
        this->_input.push_back(tokens);
        for (int u = 0; u < this->_input.size(); u++) {
            std::cout << this->_input[u].instruction << " | " << this->_input[u].value << " | " << this->_input[u].comment << std::endl;
        }
    }
}

std::vector<INPUT_LINE> Lexer::getInput() {
    return this->_input;
}

bool Lexer::getEndOfInputDetected() {
    return this->_endOfInputDetected;
}


