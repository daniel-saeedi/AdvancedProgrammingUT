#include "PlayerNotJoinedException.hpp"

const char* PlayerNotJoinedException::what() const throw()
{
    return "User not joined\n";
}