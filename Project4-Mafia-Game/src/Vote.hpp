#ifndef VOTE_H
#define VOTE_H
#include "Player.hpp"
class Vote
{
public:
	Vote(Player *voter_,Player *votee_) : voter(voter_),votee(votee_){};
	Player* get_voter(){return voter;}
	Player* get_votee(){return votee;}
	void change_votee(Player *votee_){votee = votee_;}
private:
	Player *voter;
	Player *votee;
};
#endif