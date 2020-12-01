#include "SilencedException.hpp"

const char* SilencedException::what() const throw()
{
    return "Voter is silenced\n";
}