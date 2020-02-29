//
// Created by The Champ on 2/13/2020.
//

#include "Exception.hpp"

Exception::Exception() : std::runtime_error("error") {

}

Exception::Exception(const std::string &message) throw() : std::runtime_error(message) {
    this->_message = message;
}

Exception::~Exception() {

}

Exception::Exception(Exception const &exception) throw() : std::runtime_error("error") {
    *this = exception;
}

Exception &Exception::operator=(Exception const &exception) throw() {
    if (this != &exception) {
        this->_message = exception._message;
    }

    return *this;
}

const char *Exception::what() const throw() {
    return this->_message.c_str();
}
