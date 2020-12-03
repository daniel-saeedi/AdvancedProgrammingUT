#ifndef VOTE_SYSTEM_H
#define VOTE_SYSTEM_H
#include "Player.hpp"
#include "Vote.hpp"
#include "Candidate.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

class VoteSystem
{
public:
	VoteSystem(){};
	void new_vote(Player *voter,Player *votee);
	Player* get_elected_player();
	void clear();
private:
	std::vector<Vote*> votes;
	Vote* get_vote(Player *voter);
	std::vector<Candidate> candidates;
	void create_candidate();
	bool candidate_exists(Player *player);
	void eliminate_fewer_votes();
};
#endif