#include "GameNotCreatedException.hpp"

const char* GameNotCreatedException::what() const throw()
{
    return "No game created\n";
}