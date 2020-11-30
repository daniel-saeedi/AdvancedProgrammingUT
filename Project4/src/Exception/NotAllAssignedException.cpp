#include "NotAllAssignedException.hpp"

const char* NotAllAssignedException::what() const throw()
{
    return "One or more players do not have a role\n";
}