#include "SuspectIsDeadException.hpp"

const char* SuspectIsDeadException::what() const throw()
{
    return "Suspect is dead\n";
}