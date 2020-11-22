#ifndef TEAM_H
#define TEAM_H

#include<vector>
#include "Player.hpp"
#include <iostream>

class Team
{
public:
	Team(std::vector<Player*> _players);

	int players_size(){return players.size();}
	Player* get_player(int index){return players[index];}
	void increase_won_rounds(){won_rounds++;}
	int get_won_rounds(){return won_rounds;}
	void increase_total_goals(){total_goals++;}
	int get_total_goals(){return total_goals;}
private:
	std::vector<Player*> players;
	int won_rounds;
	int total_goals;
};
#endif