#pragma once
#include <exception>

class UserNotFoundException : public std::exception {
private:
    const char* message;
public:
    UserNotFoundException(const char* msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message;
    }
};