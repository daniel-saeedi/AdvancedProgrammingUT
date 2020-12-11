#ifndef NOT_ALIVE_VOTEE_H
#define NOT_ALIVE_VOTEE_H
#include <exception>
class NotAliveVoteeException : public std::exception
{
public:
    const char* what() const throw();
};
#endif