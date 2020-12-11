#ifndef GAME_ALREADY_STARTED_H
#define GAME_ALREADY_STARTED_H
#include <exception>
class GameAlreadyStartedException : public std::exception
{
public:
    const char* what() const throw();
};
#endif