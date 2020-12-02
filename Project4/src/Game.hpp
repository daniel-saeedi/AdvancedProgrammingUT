#ifndef GAME_H
#define GAME_H
#include "Player.hpp"
#include "VoteSystem.hpp"
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
	void vote(std::string _voter,std::string _votee);
	void end_vote();
	bool get_is_night(){return is_night;}
	void night_events(std::string _voter,std::string _votee);
	void end_night();
	bool is_finished(){return finished;}
	void check_game_status();
private:
	int day_number;
	bool start;
	bool finished;
	bool allowed_to_vote;
	bool is_night;
	VoteSystem *day_vote_system;
	VoteSystem *mafia_vote_system;
	std::vector<Player*> players;
	std::vector<std::string> unassigned_players;
	Player *killed_player;
	void create_player(std::string name,std::string role);
	bool unassigned_player_exists(std::string name);
	int unassigned_player_index(std::string name);
	bool player_exists(std::string name);
	int player_index(std::string name);
	void update_player(int index,std::string role);
	void show_all_players();
	void next_day();
	void start_night();
	void show_wakeup_users();
	void mafia_vote_to_kill(Player*voter,Player *votee);
	std::vector<Player*> get_silenced_player();
	void reset_silence();
};
#endif