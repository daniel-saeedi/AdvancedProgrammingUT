#ifndef SUSPECT_IS_DEAD_EXCEPTION_H
#define SUSPECT_IS_DEAD_EXCEPTION_H
#include <exception>
class SuspectIsDeadException : public std::exception
{
public:
    const char* what() const throw();
};
#endif