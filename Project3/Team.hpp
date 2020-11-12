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
private:
	std::vector<Player*> players;

};
#endif