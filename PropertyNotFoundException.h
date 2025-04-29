#pragma once
#include <exception>

class PropertyNotFoundException : public std::exception {
private:
    const char* message;
public:
    PropertyNotFoundException(const char* msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message;
    }
};