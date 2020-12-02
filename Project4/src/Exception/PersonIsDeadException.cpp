#include "PersonIsDeadException.hpp"

const char* PersonIsDeadException::what() const throw()
{
    return "Person is dead\n";
}