#include "UserCannotWakeupException.hpp"

const char* UserCannotWakeupException::what() const throw()
{
    return "User can not wake up during night\n";
}