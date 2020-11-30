#ifndef NOT_ALL_ASSIGNED_H
#define NOT_ALL_ASSIGNED_H
#include <exception>
class NotAllAssignedException : public std::exception
{
public:
    const char* what() const throw();
};
#endif