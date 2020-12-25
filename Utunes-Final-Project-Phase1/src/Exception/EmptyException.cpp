#include "EmptyException.hpp"

const char* EmptyException::what() const throw()
{
    return "Empty\n";
}