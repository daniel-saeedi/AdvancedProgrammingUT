#ifndef VOTING_IN_PROGRESS_EXCEPTION_H
#define VOTING_IN_PROGRESS_EXCEPTION_H
#include <exception>
class VotingInProgressException : public std::exception
{
public:
    const char* what() const throw();
};
#endif