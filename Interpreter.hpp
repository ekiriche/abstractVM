//
// Created by The Champ on 2/6/2020.
//

#ifndef AVM_INTERPRETER_HPP
#define AVM_INTERPRETER_HPP

#include "IOperand.hpp"
#include "eOperand.hpp"
#include <iostream>
#include "Parser.hpp"
#include "Factory.hpp"
#include <cassert>
#include "Exception.hpp"
#include <functional>
#include <vector>
#include <numeric>
#include <string>

class Interpreter {
public:
    Interpreter(bool verboseMode);
    ~Interpreter();
    Interpreter(Interpreter const &interpreter);
    Interpreter& operator=(Interpreter const &interpreter);

    void executeCommand(PARSED_LINE line);

    void operandPush(eOperandType type, std::string value);
    void operandPop();
    void operandDump() const;
    void operandAssert(eOperandType type, std::string value);
    void operandAdd();
    void operandSub();
    void operandMul();
    void operandDiv();
    void operandMod();
    void operandPrint();

    void operandFindMax();
    void operandFindMin();
    void operandFindAvg();

    std::vector<IOperand const *> getStack();

private:
    size_t _linesExecuted;
    std::vector<IOperand const *> _stack;
    bool _verboseMode;
};


#endif //AVM_INTERPRETER_HPP
