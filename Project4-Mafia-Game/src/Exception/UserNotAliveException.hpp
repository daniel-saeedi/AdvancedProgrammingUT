#ifndef USER_NOT_ALIVE_EXCEPTION_H
#define USER_NOT_ALIVE_EXCEPTION_H
#include <exception>
class UserNotAliveException : public std::exception
{
public:
    const char* what() const throw();
};
#endif