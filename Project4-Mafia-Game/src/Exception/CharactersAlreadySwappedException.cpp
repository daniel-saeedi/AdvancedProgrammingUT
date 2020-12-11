#include "CharactersAlreadySwappedException.hpp"

const char* CharactersAlreadySwappedException::what() const throw()
{
    return "Characters already swapped\n";
}