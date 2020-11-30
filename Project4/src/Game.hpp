#ifndef GAME_H
#define GAME_H
#include "Player.hpp"
#include <iostream>
#include <string>
#include <vector>
class Game
{
public:
	Game();

	void add_unassgined_player(std::string name);
	void assign_role(std::string name,std::string role);
	void create_player(std::string name,std::string role);
private:
	std::vector<Player*> players;
	std::vector<std::string> unassigned_players;
	bool unassigned_player_exists(std::string name);
};
#endif