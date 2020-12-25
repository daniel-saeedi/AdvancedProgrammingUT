#ifndef BAD_REQUEST_EXCEPTION_H
#define BAD_REQUEST_EXCEPTION_H
#include <exception>
class BadRequestException : public std::exception
{
public:
    const char* what() const throw();
};
#endif