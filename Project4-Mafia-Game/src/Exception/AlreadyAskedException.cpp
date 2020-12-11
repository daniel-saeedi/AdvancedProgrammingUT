#include "AlreadyAskedException.hpp"

const char* AlreadyAskedException::what() const throw()
{
    return "Detective has already asked\n";
}