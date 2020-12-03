#ifndef CHARACTERS_ALREADY_SWAPPED_EXCEPTION_H
#define CHARACTERS_ALREADY_SWAPPED_EXCEPTION_H
#include <exception>
class CharactersAlreadySwappedException : public std::exception
{
public:
    const char* what() const throw();
};
#endif