//
// Created by The Champ on 2/14/2020.
//

#ifndef AVM_EOPERAND_HPP
#define AVM_EOPERAND_HPP

#include "IOperand.hpp"
#include "Factory.hpp"
#include <iostream>

template <typename T>
class eOperand : public IOperand {
public:
    eOperand();
    eOperand(T value, eOperandType type);
    ~eOperand();
    IOperand const &operator=(eOperand const &operand);
    eOperand(eOperand const &operand);

    IOperand const * operator+( IOperand const & rhs ) const;
    IOperand const * operator-( IOperand const & rhs ) const;
    IOperand const * operator*( IOperand const & rhs ) const;
    IOperand const * operator/( IOperand const & rhs ) const;
    IOperand const * operator%( IOperand const & rhs ) const;

    int getPrecision() const;
    eOperandType getType( void ) const;
    std::string const &toString() const;

    T getValue() const;

private:
    T _value;
    std::string _stringValue;
    eOperandType _type;
};


#endif //AVM_EOPERAND_HPP
