//
// Created by The Champ on 1/29/2020.
//

#ifndef AVM_LEXER_HPP
#define AVM_LEXER_HPP

#include <iostream>
#include <vector>

struct INPUT_LINE {
    std::string instruction;
    std::string value;
    std::string comment;
};

class Lexer {
public:
    Lexer();
    ~Lexer();
    Lexer(Lexer const &lexer);
    Lexer& operator=(Lexer const &lexer);

    void analyseInputLine(std::string &line);

    std::vector<INPUT_LINE> getInput();
    std::vector<std::string> getErrors();

private:
    std::vector<INPUT_LINE> _input;
    std::vector<std::string> _errors;
};


#endif //AVM_LEXER_HPP
