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
	~CommandHandler();
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
	void is_command_valid(int info_size,int headers_size);
	void post_commands(vector<string> tokenized_input);
	void get_commands(vector<string> tokenized_input);
	void delete_commands(vector<string> tokenized_input);
	std::map<std::string,std::string> split_by_headers(vector<std::string> headers,vector<std::string> info);
	void signup(vector<string> info);
	void login(vector<string> info);
	void new_like(vector<string> info);
	void add_playlist(vector<string> info);
	void add_song_to_playlist(vector<string> info);
	void add_comment(vector<string> info);
	void add_filter(vector<string> info);
	void add_artist_filter(vector<string> info);
	void add_publish_year_filter(vector<string> info);
	void add_likes_filter(vector<string> info);
	void get_song(vector<string> info);
	void get_playlists(vector<string> info);
	void get_playlist_songs(vector<string> info);
	void get_comments(vector<string> info);
	void delete_like(vector<string> info);
	void delete_playlist_song(vector<string> info);
};
#endif