#include "VotingInProgressException.hpp"

const char* VotingInProgressException::what() const throw()
{
    return "Voting in progress\n";
}