#ifndef ILLEGAL_ARGUMENT
#define ILLEGAL_ARGUMENT

#include <stdexcept>
#include <string>

class IllegalArgumentException : public std::logic_error
{
        public:
        IllegalArgumentException(const std::string& message =""):
            logic_error("Logical Error:" + message){}
};

#endif