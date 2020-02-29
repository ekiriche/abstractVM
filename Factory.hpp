//
// Created by The Champ on 2/13/2020.
//

#ifndef AVM_FACTORY_HPP
#define AVM_FACTORY_HPP

#include "IOperand.hpp"
#include "eOperand.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "Exception.hpp"

class Factory {
public:
    Factory();
    ~Factory();
    Factory &operator=(Factory const &factory);
    Factory(Factory const &factory);
    IOperand const * createOperand( eOperandType type, std::string const & value ) const;

private:
    IOperand const * createInt8( std::string const & value ) const;
    IOperand const * createInt16( std::string const & value ) const;
    IOperand const * createInt32( std::string const & value ) const;
    IOperand const * createFloat( std::string const & value ) const;
    IOperand const * createDouble( std::string const & value ) const;

    std::vector<IOperand const *(Factory::*)(std::string const &name) const> _createFuncs;
};


#endif //AVM_FACTORY_HPP
