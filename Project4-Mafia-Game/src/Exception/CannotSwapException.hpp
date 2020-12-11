#ifndef CANNOT_SWAP_EXCEPTION_H
#define CANNOT_SWAP_EXCEPTION_H
#include <exception>
class CannotSwapException : public std::exception
{
public:
    const char* what() const throw();
};
#endif