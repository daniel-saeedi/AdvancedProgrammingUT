#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H
#include "Utunes.hpp"
#include "Song.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
using namespace std;

class CommandHandler
{
public:
	CommandHandler(char* file);
	void run();
private:
	Utunes *utunes;
	vector<string> tokenize_input(string input);
	vector<Song*> get_records(char* file);
	vector<vector<string>> read_csv(char* file);
	vector<string> split(string line, char delimiter);
	vector<Song*> tokenize_table(vector<vector<string>> table);
	Song* tokenize(vector<string> raw,vector<string> header);
	int find_index_in_vector(const vector<string>& vec, string s);
	void post_commands(vector<string> tokenized_input);
};
#endif