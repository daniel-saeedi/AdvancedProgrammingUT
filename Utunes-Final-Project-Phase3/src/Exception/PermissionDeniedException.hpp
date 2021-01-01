#ifndef PERMISSION_DENIED_EXCEPTION_H
#define PERMISSION_DENIED_EXCEPTION_H
#include <exception>
class PermissionDeniedException : public std::exception
{
public:
    const char* what() const throw();
};
#endif