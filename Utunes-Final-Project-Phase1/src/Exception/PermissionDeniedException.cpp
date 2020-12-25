#include "PermissionDeniedException.hpp"

const char* PermissionDeniedException::what() const throw()
{
    return "Permission Denied\n";
}