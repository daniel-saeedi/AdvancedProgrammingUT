#include "Team.hpp"


Team::Team(std::vector<Player*> _players)
{
	players = _players;
	won_rounds = 0;
	total_goals = 0;
}