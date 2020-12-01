#ifndef SILENCED_H
#define SILENCED_H
#include <exception>
class SilencedException : public std::exception
{
public:
    const char* what() const throw();
};
#endif