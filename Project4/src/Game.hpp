#ifndef GAME_H
#define GAME_H
#include "Player.hpp"
#include "VoteSystem.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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
	void get_game_state();
	void swap_character(std::string name1,std::string name2);
private:
	int day_number;
	bool start;
	bool finished;
	bool voting_in_progress;
	bool already_asked_to_swap;
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
	void reset();
	std::vector<int> count_players();
	void show_killed_player();
	void show_silenced_player();
	void swap_players(Player *player1,Player *player2);
};
#endif