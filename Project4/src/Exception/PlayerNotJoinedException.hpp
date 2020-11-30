#ifndef PLAYERS_NOT_JOINED_EXCEPTION_H
#define PLAYERS_NOT_JOINED_EXCEPTION_H
#include <exception>
class PlayerNotJoinedException : public std::exception
{
public:
    const char* what() const throw();
};
#endif