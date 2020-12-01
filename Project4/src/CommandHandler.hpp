#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H
#include "Game.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class CommandHandler
{
public:
	CommandHandler();
	void run();
private:
	Game *game;

	vector<string> tokenize_input(string input);
	void create_game(vector<string> tokenized_input);
	void assign_role(vector<string> tokenized_input);
	void start_game();
	void day_vote(vector<string> tokenized_input);
	void night_vote(vector<string> tokenized_input);
	void day_command(string command_type,vector<string> tokenized_input);
	void night_command(string command_type,vector<string> tokenized_input);
};
#endif