#ifndef NOSUCHELEMENT
#define NOSUCHELEMENT

#include <stdexcept>
#include <string>

class NoSuchElementException : public std::logic_error
{
    public:
        NoSuchElementException(const std::string& message = ""):
            logic_error("Logical Error: " + message){}
};

#endif