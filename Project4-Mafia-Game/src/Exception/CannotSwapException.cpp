#include "CannotSwapException.hpp"

const char* CannotSwapException::what() const throw()
{
    return "Can't swap before end of night\n";
}