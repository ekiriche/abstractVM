//
// Created by The Champ on 2/13/2020.
//

#include "Factory.hpp"
#include "eOperand.hpp"
#include <exception>
#include <cfloat>

Factory::Factory() {
    this->_createFuncs.push_back(&Factory::createInt8);
    this->_createFuncs.push_back(&Factory::createInt16);
    this->_createFuncs.push_back(&Factory::createInt32);
    this->_createFuncs.push_back(&Factory::createFloat);
    this->_createFuncs.push_back(&Factory::createDouble);
}

Factory::~Factory() {}

Factory &Factory::operator=(Factory const &factory) {
    if (this != &factory) {
        this->_createFuncs = factory._createFuncs;
    }
    return *this;
}

Factory::Factory(Factory const &factory) {
    *this = factory;
}

IOperand const *Factory::createOperand(eOperandType type, std::string const &value) const {
    return ((this->*_createFuncs[type])(value));
}

IOperand const *Factory::createInt8(std::string const &value) const {
    int64_t num = std::stoll(value);
    if (num > INT8_MAX) {
        throw Exception("Overflow on create value " + value + " with type int8");
    } else if (num < INT8_MIN) {
        throw Exception("Underflow on create value " + value + " with type int8");
    }

    return (new eOperand<int8_t>(static_cast<int8_t>(num), Int8));
}

IOperand const *Factory::createInt16(std::string const &value) const {
    int64_t num = std::stoll(value);
    if (num > INT16_MAX) {
        throw Exception("Overflow on create value " + value + " with type int16");
    } else if (num < INT16_MIN) {
        throw Exception("Underflow on create value " + value + " with type int16");
    }

    return (new eOperand<int16_t>(static_cast<int16_t>(num), Int16));
}

IOperand const *Factory::createInt32(std::string const &value) const {
    int64_t num = std::stoll(value);
    if (num > INT32_MAX) {
        throw Exception("Overflow on create value " + value + " with type int32");
    } else if (num < INT32_MIN) {
        throw Exception("Underflow on create value " + value + " with type int32");
    }

    return (new eOperand<int32_t>(static_cast<int32_t>(num), Int32));
}

IOperand const *Factory::createFloat(std::string const &value) const {
    long double num = std::stold(value);
//    if (num > std::numeric_limits<float>::max()) {
//        throw Exception("Overflow on create value " + value + " with type float");
//    } else if (num < std::numeric_limits<float>::min()) {
//        throw Exception("Underflow on create value " + value + " with type float");
//    }

    return (new eOperand<float>(static_cast<float>(num), Float));
}

IOperand const *Factory::createDouble(std::string const &value) const {
    long double num = std::stold(value);
//    if (num > DBL_MAX) {
//        throw Exception("Overflow on create value " + value + " with type double");
//    } else if (num < DBL_MIN) {
//        throw Exception("Underflow on create value " + value + " with type double");
//    }

    return (new eOperand<double>(static_cast<double>(num), Double));
}