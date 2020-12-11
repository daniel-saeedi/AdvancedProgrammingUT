#ifndef GAME_NOT_CREATED_EXCEPTION_H
#define GAME_NOT_CREATED_EXCEPTION_H
#include <exception>
class GameNotCreatedException : public std::exception
{
public:
    const char* what() const throw();
};
#endif