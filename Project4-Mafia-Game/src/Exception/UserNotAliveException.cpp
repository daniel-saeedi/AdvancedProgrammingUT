#include "UserNotAliveException.hpp"

const char* UserNotAliveException::what() const throw()
{
    return "User is dead\n";
}