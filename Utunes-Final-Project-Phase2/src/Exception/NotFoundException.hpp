#ifndef NOT_FOUND_EXCEPTION_H
#define NOT_FOUND_EXCEPTION_H
#include <exception>
class NotFoundException : public std::exception
{
public:
    const char* what() const throw();
};
#endif