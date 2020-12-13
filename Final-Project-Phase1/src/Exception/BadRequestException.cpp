#include "BadRequestException.hpp"

const char* BadRequestException::what() const throw()
{
    return "Bad Request\n";
}