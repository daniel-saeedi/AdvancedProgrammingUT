#ifndef ALREADY_ASKED_EXCEPTION_H
#define ALREADY_ASKED_EXCEPTION_H
#include <exception>
class AlreadyAskedException : public std::exception
{
public:
    const char* what() const throw();
};
#endif