#include "AlreadyHealedException.hpp"

const char* AlreadyHealedException::what() const throw()
{
    return "Doctor has already healed\n";
}