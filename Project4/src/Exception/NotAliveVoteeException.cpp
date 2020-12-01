#include "NotAliveVoteeException.hpp"

const char* NotAliveVoteeException::what() const throw()
{
    return "Votee already dead\n";
}