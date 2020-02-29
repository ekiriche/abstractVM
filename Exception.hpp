//
// Created by The Champ on 2/13/2020.
//

#ifndef AVM_EXCEPTION_HPP
#define AVM_EXCEPTION_HPP

#include <iostream>
#include <exception>
#include <string>

class Exception : public std::runtime_error {
public:
    Exception(const std::string &message) throw();
    ~Exception();
    Exception(Exception const &exception) throw();
    Exception &operator=(Exception const &exception) throw();
    const char *what() const throw();
private:
    Exception();
    std::string _message;

};


#endif //AVM_EXCEPTION_HPP
