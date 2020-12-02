#ifndef ALREADY_HEALED_EXCEPTION_H
#define ALREADY_HEALED_EXCEPTION_H
#include <exception>
class AlreadyHealedException : public std::exception
{
public:
    const char* what() const throw();
};
#endif