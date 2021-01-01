#ifndef EMPTY_EXCEPTION_H
#define EMPTY_EXCEPTION_H
#include <exception>
class EmptyException : public std::exception
{
public:
    const char* what() const throw();
};
#endif