#ifndef USER_CANNOT_WAKEUP_H
#define USER_CANNOT_WAKEUP_H
#include <exception>
class UserCannotWakeupException : public std::exception
{
public:
    const char* what() const throw();
};
#endif