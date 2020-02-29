//
// Created by The Champ on 2/6/2020.
//

#include "Interpreter.hpp"

Interpreter::Interpreter(bool verboseMode) {
    this->_verboseMode = verboseMode;
    this->_linesExecuted = 0;
}

Interpreter::~Interpreter() {

}

Interpreter::Interpreter(Interpreter const &interpreter) {
    *this = interpreter;
}

Interpreter &Interpreter::operator=(Interpreter const &interpreter) {
    if (this != &interpreter) {
        this->_stack = interpreter._stack;
        this->_verboseMode = interpreter._verboseMode;
        this->_linesExecuted = interpreter._linesExecuted;
    }
    return *this;
}

void Interpreter::executeCommand(PARSED_LINE line) {
    if (line.instruction == "push") {
        this->operandPush(line.type, line.value);
    } else if (line.instruction == "pop") {
        this->operandPop();
    } else if (line.instruction == "dump") {
        this->operandDump();
    } else if (line.instruction == "assert") {
        this->operandAssert(line.type, line.value);
    } else if (line.instruction == "add") {
        this->operandAdd();
    } else if (line.instruction == "sub") {
        this->operandSub();
    } else if (line.instruction == "mul") {
        this->operandMul();
    } else if (line.instruction == "div") {
        this->operandDiv();
    } else if (line.instruction == "mod") {
        this->operandMod();
    } else if (line.instruction == "print") {
        this->operandPrint();
    } else if (line.instruction == "exit") {
        exit(0);
    }
    this->_linesExecuted++;
}

void Interpreter::operandPush(eOperandType type, std::string value) {
    try {
        this->_stack.push_back(Factory().createOperand(type, value));
        if (this->_verboseMode) {
            std::cout << "Pushed to stack value " << this->_stack[this->_stack.size() - 1]->toString() << std::endl;
        }
    } catch (Exception &exception) {
        std::cout << "Error occurred on line " << this->_linesExecuted + 1 << ": " << exception.what() << std::endl;
        exit(1);
    } catch (std::exception &e) {
        std::cout << "Error occurred on line " << this->_linesExecuted + 1 << ": " << e.what() << std::endl;
        exit(1);
    }
}

void Interpreter::operandPop() {
    try {
        if (!this->_stack.size()) {
            throw Exception("Pop on empty stack");
        }
        if (this->_verboseMode) {
            std::cout << "Popped from stack value " << this->_stack.at(this->_stack.size() - 1)->toString() << std::endl;
        }
        this->_stack.pop_back();
    } catch (Exception &exception) {
        std::cout << "Error occurred on line " << this->_linesExecuted + 1 << ": " << exception.what() << std::endl;
        exit(1);
    } catch (std::exception &e) {
        std::cout << "Error occurred on line " << this->_linesExecuted + 1 << ": " << e.what() << std::endl;
        exit(1);
    }
}

void Interpreter::operandDump() const {
    if (this->_verboseMode) {
        std::cout << "=============== DUMP START ===============" << std::endl;
    }

    for (unsigned int i = 0; i < this->_stack.size(); i++) {
        std::cout << this->_stack[i]->toString() << std::endl;
    }

    if (this->_verboseMode) {
        std::cout << "=============== DUMP END ===============" << std::endl;
    }
}

void Interpreter::operandAssert(eOperandType type, std::string value) {
    try {
        if (!this->_stack.size() || this->_stack[this->_stack.size() - 1]->getType() != type ||
                std::stod(this->_stack[this->_stack.size() - 1]->toString()) != std::stod(value)) {
            throw Exception("Assert check for value " + value + " failed");
        }

        if (this->_verboseMode) {
            std::cout << "Assert check for value " << value << " passed" << std::endl;
        }
    } catch (Exception &exception) {
        std::cout << "Error occurred on line " << this->_linesExecuted + 1 << ": " << exception.what() << std::endl;
        exit(1);
    } catch (std::exception &e) {
        std::cout << "Error occurred on line " << this->_linesExecuted + 1 << ": " << e.what() << std::endl;
        exit(1);
    }
}

void Interpreter::operandAdd() {
    try {
        if (this->_stack.size() < 2) {
            throw Exception("Add on less then two operands in stack");
        }

        this->_stack.push_back(*this->_stack[this->_stack.size() - 2] + *this->_stack[this->_stack.size() - 1]);

        if (this->_verboseMode) {
            std::cout << "Added values " << this->_stack[this->_stack.size() - 3]->toString() << " and " <<
                this->_stack[this->_stack.size() - 2]->toString() << ". The result is " <<
                this->_stack[this->_stack.size() - 1]->toString() << std::endl;
        }

        this->_stack.erase(this->_stack.begin() + this->_stack.size() - 2);
        this->_stack.erase(this->_stack.begin() + this->_stack.size() - 2);


    } catch (Exception &exception) {
        std::cout << "Error occurred on line " << this->_linesExecuted + 1 << ": " << exception.what() << std::endl;
        exit(1);
    } catch (std::exception &e) {
        std::cout << "Error occurred on line " << this->_linesExecuted + 1 << ": " << e.what() << std::endl;
        exit(1);
    }
}

void Interpreter::operandSub() {
    try {
        if (this->_stack.size() < 2) {
            throw Exception("Sub on less then two operands in stack");
        }

        this->_stack.push_back(*this->_stack[this->_stack.size() - 2] - *this->_stack[this->_stack.size() - 1]);

        if (this->_verboseMode) {
            std::cout << "Subbed values " << this->_stack[this->_stack.size() - 3]->toString() << " and " <<
                      this->_stack[this->_stack.size() - 2]->toString() << ". The result is " <<
                      this->_stack[this->_stack.size() - 1]->toString() << std::endl;
        }

        this->_stack.erase(this->_stack.begin() + this->_stack.size() - 2);
        this->_stack.erase(this->_stack.begin() + this->_stack.size() - 2);
    } catch (Exception &exception) {
        std::cout << "Error occurred on line " << this->_linesExecuted + 1 << ": " << exception.what() << std::endl;
        exit(1);
    } catch (std::exception &e) {
        std::cout << "Error occurred on line " << this->_linesExecuted + 1 << ": " << e.what() << std::endl;
        exit(1);
    }
}

void Interpreter::operandMul() {
    try {
        if (this->_stack.size() < 2) {
            throw Exception("Mul on less then two operands in stack");
        }

        this->_stack.push_back(*this->_stack[this->_stack.size() - 2] * *this->_stack[this->_stack.size() - 1]);

        if (this->_verboseMode) {
            std::cout << "Multiplied values " << this->_stack[this->_stack.size() - 3]->toString() << " and " <<
                      this->_stack[this->_stack.size() - 2]->toString() << ". The result is " <<
                      this->_stack[this->_stack.size() - 1]->toString() << std::endl;
        }

        this->_stack.erase(this->_stack.begin() + this->_stack.size() - 2);
        this->_stack.erase(this->_stack.begin() + this->_stack.size() - 2);
    } catch (Exception &exception) {
        std::cout << "Error occurred on line " << this->_linesExecuted + 1 << ": " << exception.what() << std::endl;
        exit(1);
    } catch (std::exception &e) {
        std::cout << "Error occurred on line " << this->_linesExecuted + 1 << ": " << e.what() << std::endl;
        exit(1);
    }
}

void Interpreter::operandDiv() {
    try {
        if (this->_stack.size() < 2) {
            throw Exception("Div on less then two operands in stack");
        }

        this->_stack.push_back(*this->_stack[this->_stack.size() - 2] / *this->_stack[this->_stack.size() - 1]);

        if (this->_verboseMode) {
            std::cout << "Divided values " << this->_stack[this->_stack.size() - 3]->toString() << " and " <<
                      this->_stack[this->_stack.size() - 2]->toString() << ". The result is " <<
                      this->_stack[this->_stack.size() - 1]->toString() << std::endl;
        }

        this->_stack.erase(this->_stack.begin() + this->_stack.size() - 2);
        this->_stack.erase(this->_stack.begin() + this->_stack.size() - 2);
    } catch (Exception &exception) {
        std::cout << "Error occurred on line " << this->_linesExecuted + 1 << ": " << exception.what() << std::endl;
        exit(1);
    } catch (std::exception &e) {
        std::cout << "Error occurred on line " << this->_linesExecuted + 1 << ": " << e.what() << std::endl;
        exit(1);
    }
}

void Interpreter::operandMod() {
    try {
        if (this->_stack.size() < 2) {
            throw Exception("Mod on less then two operands");
        }

        this->_stack.push_back(*this->_stack[this->_stack.size() - 2] % *this->_stack[this->_stack.size() - 1]);

        if (this->_verboseMode) {
            std::cout << "Moduled values " << this->_stack[this->_stack.size() - 3]->toString() << " and " <<
                      this->_stack[this->_stack.size() - 2]->toString() << ". The result is " <<
                      this->_stack[this->_stack.size() - 1]->toString() << std::endl;
        }

        this->_stack.erase(this->_stack.begin() + this->_stack.size() - 2);
        this->_stack.erase(this->_stack.begin() + this->_stack.size() - 2);
    } catch (Exception &exception) {
        std::cout << "Error occurred on line " << this->_linesExecuted + 1 << ": " << exception.what() << std::endl;
        exit(1);
    } catch (std::exception &e) {
        std::cout << "Error occurred on line " << this->_linesExecuted + 1 << ": " << e.what() << std::endl;
        exit(1);
    }
}

void Interpreter::operandPrint() {
    try {
        if (!this->_stack.size()) {
            throw Exception("Print on empty stack");
        }
        if (this->_stack[this->_stack.size() - 1]->getType() != Int8) {
            throw Exception("Print command on non-int8 value type");
        }
        std::cout << static_cast<int8_t>(std::stoi(this->_stack[this->_stack.size() - 1]->toString())) << std::endl;
    } catch (Exception &exception) {
        std::cout << "Error occurred on line " << this->_linesExecuted + 1 << ": " << exception.what() << std::endl;
        exit(1);
    } catch (std::exception &e) {
        std::cout << "Error occurred on line " << this->_linesExecuted + 1 << ": " << e.what() << std::endl;
        exit(1);
    }
}

std::vector<IOperand const *> Interpreter::getStack() {
    return this->_stack;
}
