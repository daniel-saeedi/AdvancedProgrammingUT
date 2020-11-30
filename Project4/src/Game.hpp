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
	void start_game();
private:
	bool start;
	std::vector<Player*> players;
	std::vector<std::string> unassigned_players;
	void create_player(std::string name,std::string role);
	bool unassigned_player_exists(std::string name);
	int unassigned_player_index(std::string name);
	bool player_exists(std::string name);
	int player_index(std::string name);
	void update_player(int index,std::string role);
	void show_all_players();
};
#endif