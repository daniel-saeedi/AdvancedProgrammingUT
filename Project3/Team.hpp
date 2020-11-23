#ifndef TEAM_H
#define TEAM_H

#include<vector>
#include "Player.hpp"
#include <iostream>

class Team
{
public:
	Team(std::vector<Player*> _players);

	int PlayerSize(){return players.size();}
	Player* GetPlayer(int index){return players[index];}
	void IncreaseWonRounds(){won_rounds++;}
	int GetWonRounds(){return won_rounds;}
	void IncreaseTotalGoals(){total_goals++;}
	int GetTotalGoals(){return total_goals;}
private:
	std::vector<Player*> players;
	int won_rounds;
	int total_goals;
};
#endif