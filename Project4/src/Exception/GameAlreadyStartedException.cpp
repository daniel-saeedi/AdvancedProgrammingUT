#include "GameAlreadyStartedException.hpp"

const char* GameAlreadyStartedException::what() const throw()
{
    return "Game has already started\n";
}