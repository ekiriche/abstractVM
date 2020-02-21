//
// Created by The Champ on 2/14/2020.
//

#include "eOperand.hpp"
#include <cmath>

template<typename T>
eOperand<T>::eOperand() {}

template<typename T>
eOperand<T>::~eOperand() {}

template<typename T>
IOperand const &eOperand<T>::operator=(eOperand const &operand) {
    if (this != &operand) {
        this->_type = operand._type;
        this->_value = operand._value;
    }
    return *this;
}

template<typename T>
eOperand<T>::eOperand(eOperand const &operand) {
    *this = operand;
}

template<typename T>
eOperand<T>::eOperand(T value, eOperandType type) {
    this->_value = value;
    this->_type = type;
    this->_stringValue = std::to_string(value);
}

template<typename T>
int eOperand<T>::getPrecision() const {
    return this->_type;
}

template<typename T>
eOperandType eOperand<T>::getType() const {
    return this->_type;
}

template<typename T>
IOperand const *eOperand<T>::operator+(IOperand const &rhs) const {
    eOperandType newType;
    std::string newStringValue;

    this->_type >= rhs.getType() ? newType = this->_type : newType = rhs.getType();

    newType == Float || newType == Double ?
        newStringValue = std::to_string(std::stold(this->_stringValue) + std::stold(rhs.toString())) :
                newStringValue = std::to_string(std::stoll(this->_stringValue) + std::stoll(rhs.toString()));

    return (Factory().createOperand(newType, newStringValue));
}

template<typename T>
IOperand const *eOperand<T>::operator-(IOperand const &rhs) const {
    eOperandType newType;
    std::string newStringValue;

    this->_type >= rhs.getType() ? newType = this->_type : newType = rhs.getType();

    newType == Float || newType == Double ?
            newStringValue = std::to_string(std::stold(this->_stringValue) - std::stold(rhs.toString())) :
            newStringValue = std::to_string(std::stoll(this->_stringValue) - std::stoll(rhs.toString()));

    return (Factory().createOperand(newType, newStringValue));
}

template<typename T>
IOperand const *eOperand<T>::operator*(IOperand const &rhs) const {
    eOperandType newType;
    std::string newStringValue;

    this->_type >= rhs.getType() ? newType = this->_type : newType = rhs.getType();

    newType == Float || newType == Double ?
            newStringValue = std::to_string(std::stold(this->_stringValue) * std::stold(rhs.toString())) :
            newStringValue = std::to_string(std::stoll(this->_stringValue) * std::stoll(rhs.toString()));

    return (Factory().createOperand(newType, newStringValue));
}

template<typename T>
IOperand const *eOperand<T>::operator/(IOperand const &rhs) const {
    eOperandType newType;
    std::string newStringValue;

    this->_type >= rhs.getType() ? newType = this->_type : newType = rhs.getType();

    newType == Float || newType == Double ?
            newStringValue = std::to_string(std::stold(this->_stringValue) / std::stold(rhs.toString())) :
            newStringValue = std::to_string(std::stoll(this->_stringValue) / std::stoll(rhs.toString()));

    return (Factory().createOperand(newType, newStringValue));
}

template<typename T>
IOperand const *eOperand<T>::operator%(IOperand const &rhs) const {
    eOperandType newType;
    std::string newStringValue;

    this->_type >= rhs.getType() ? newType = this->_type : newType = rhs.getType();

    newType == Float || newType == Double ?
            newStringValue = std::to_string(std::fmod(std::stold(this->_stringValue), std::stold(rhs.toString()))) :
            newStringValue = std::to_string(std::stoll(this->_stringValue) % std::stoll(rhs.toString()));

    return (Factory().createOperand(newType, newStringValue));
}

template<typename T>
T eOperand<T>::getValue() const {
    return this->_value;
}

template<typename T>
std::string const &eOperand<T>::toString() const {
    return this->_stringValue;
}

template class eOperand<int8_t>;
template class eOperand<int16_t>;
template class eOperand<int32_t>;
template class eOperand<float>;
template class eOperand<double>;