#pragma once
#include <exception>

class UserAlreadyExistsException : public std::exception {
private:
    const char* message;
public:
    UserAlreadyExistsException(const char* msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message;
    }
};