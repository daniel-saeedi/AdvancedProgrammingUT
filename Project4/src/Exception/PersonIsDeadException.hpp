#ifndef PERSON_IS_DEAD_EXCEPTION_H
#define PERSON_IS_DEAD_EXCEPTION_H
#include <exception>
class PersonIsDeadException : public std::exception
{
public:
    const char* what() const throw();
};
#endif