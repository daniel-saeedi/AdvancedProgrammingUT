#ifndef CANDIDATES_H
#define CANDIDATES_H
#include "Player.hpp"
class Candidate
{
public:
	Candidate(Player *votee_) : votee(votee_),number_of_votes(1){};
	int get_number_of_votes(){return number_of_votes;}
	Player* get_votee(){return votee;}
	void increase_vote(){number_of_votes++;}
private:
	Player* votee;
	int number_of_votes;
};
#endif