#include "CommandHandler.hpp"
const char CSV_DELIMITER = ',';
constexpr char POST[] = "POST";
constexpr char GET[] = "GET";
constexpr char DELETE[] = "DELETE";
constexpr char SINGUP[] = "signup";
constexpr char LOGIN[] = "login";
constexpr char LOGOUT[] = "logout";
constexpr char SONGS[] = "songs";
constexpr char LIKES[] = "likes";
constexpr char PLAYLISTS[] = "playlists";
constexpr char PLAYLISTS_SONGS[] = "playlists_songs";
constexpr char USERS[] = "users";
constexpr char COMMENTS[] = "comments";
constexpr char FILTERS[] = "filters";
//Headers of csv file
constexpr char ID[] = "id";
constexpr char TITLE[] = "title";
constexpr char ARTIST[] = "artist";
constexpr char RELEASE_YEAR[] = "release_year";
constexpr char LINK[] = "link";

CommandHandler::CommandHandler(char* file)
{
	vector<Song*> songs = get_records(file);
	utunes = new Utunes(songs);
}

void CommandHandler::run()
{
	const int COMMAND_TYPE_INDEX = 0;
	string input;
	while (getline(cin, input))
	{
		if(input != "")
		{
			vector<string> tokenized_input = tokenize_input(input);
			const string command_type = tokenized_input[COMMAND_TYPE_INDEX];
			try
			{
				if(command_type == POST) post_commands(tokenized_input);
				else if(command_type == GET) get_commands(tokenized_input);
				else if(command_type == DELETE) delete_commands(tokenized_input);
			}
			catch(const exception& error)
			{
				cerr << error.what();
			}
		}
	}
}

void CommandHandler::post_commands(vector<string> tokenized_input)
{
	const int OPERATION_INDEX = 1;
	const int QUESTION_MARK_INDEX = 3;
	string operation = tokenized_input[OPERATION_INDEX];
	if(operation == SINGUP)
	{
		tokenized_input.erase(tokenized_input.begin(), tokenized_input.begin() + QUESTION_MARK_INDEX);
		utunes->signup(tokenized_input);
	}
	else if(operation == LOGIN)
	{
		tokenized_input.erase(tokenized_input.begin(), tokenized_input.begin() + QUESTION_MARK_INDEX);
		utunes->login(tokenized_input);
	}
	else if(operation == LOGOUT)
	{
		utunes->logout();
	}
	else if(operation == LIKES)
	{
		utunes->check_login();
		tokenized_input.erase(tokenized_input.begin(), tokenized_input.begin() + QUESTION_MARK_INDEX);
		utunes->new_like(tokenized_input);
	}
	else if(operation == PLAYLISTS)
	{
		utunes->check_login();
		tokenized_input.erase(tokenized_input.begin(), tokenized_input.begin() + QUESTION_MARK_INDEX);
		utunes->add_playlist(tokenized_input);
	}
	else if(operation == PLAYLISTS_SONGS)
	{
		utunes->check_login();
		tokenized_input.erase(tokenized_input.begin(), tokenized_input.begin() + QUESTION_MARK_INDEX);
		utunes->add_song_to_playlist(tokenized_input);
	}
	else if(operation == COMMENTS)
	{
		utunes->check_login();
		tokenized_input.erase(tokenized_input.begin(), tokenized_input.begin() + QUESTION_MARK_INDEX);
		utunes->add_comment(tokenized_input);
	}
	else if(operation == FILTERS)
	{
		utunes->check_login();
		tokenized_input.erase(tokenized_input.begin(), tokenized_input.begin() + QUESTION_MARK_INDEX);
		utunes->add_filter(tokenized_input);
	}
}

void CommandHandler::get_commands(vector<string> tokenized_input)
{
	utunes->check_login();
	const int OPERATION_INDEX = 1;
	const int QUESTION_MARK_INDEX = 3;
	string operation = tokenized_input[OPERATION_INDEX];
	if(operation == SONGS)
	{
		if(tokenized_input.size() == 2) utunes->get_songs();
		else
		{
			tokenized_input.erase(tokenized_input.begin(), tokenized_input.begin() + QUESTION_MARK_INDEX);
			utunes->get_song(tokenized_input);
		}
	}
	else if(operation == LIKES)
	{
		utunes->show_likes();
	}
	else if(operation == PLAYLISTS)
	{
		tokenized_input.erase(tokenized_input.begin(), tokenized_input.begin() + QUESTION_MARK_INDEX);
		utunes->get_playlists(tokenized_input);
	}
	else if(operation == PLAYLISTS_SONGS)
	{
		tokenized_input.erase(tokenized_input.begin(), tokenized_input.begin() + QUESTION_MARK_INDEX);
		utunes->get_playlist_songs(tokenized_input);
	}
	else if(operation == USERS)
	{
		utunes->get_users();
	}
	else if(operation == COMMENTS)
	{
		tokenized_input.erase(tokenized_input.begin(), tokenized_input.begin() + QUESTION_MARK_INDEX);
		utunes->get_comments(tokenized_input);
	}
}

void CommandHandler::delete_commands(vector<string> tokenized_input)
{
	utunes->check_login();
	const int OPERATION_INDEX = 1;
	const int QUESTION_MARK_INDEX = 3;
	string operation = tokenized_input[OPERATION_INDEX];
	if(operation == LIKES)
	{
		tokenized_input.erase(tokenized_input.begin(), tokenized_input.begin() + QUESTION_MARK_INDEX);
		utunes->delete_like(tokenized_input);
	}
	else if(operation == PLAYLISTS_SONGS)
	{
		tokenized_input.erase(tokenized_input.begin(), tokenized_input.begin() + QUESTION_MARK_INDEX);
		utunes->delete_playlist_song(tokenized_input);
	}
	else if(operation == FILTERS)
	{
		utunes->delete_filters();
	}
}

vector<string> CommandHandler::tokenize_input(string input)
{
	stringstream input_string_stream(input);
	return vector<string>(istream_iterator<string>(input_string_stream),istream_iterator<string>());
}


vector<Song*> CommandHandler::get_records(char* file)
{
    vector<vector<string>> table;
    table = read_csv(file);
    return tokenize_table(table);
}

vector<vector<string>> CommandHandler::read_csv(char* file)
{
    string line;
    fstream fin;
    fin.open(file, ios::in);
    vector<vector<string>> table;
    while(getline(fin, line))
    {
		table.push_back(split(line, CSV_DELIMITER));
    }
    return table;
}

vector<string> CommandHandler::split(string line, char delimiter)
{
	stringstream stream(line);
	vector<string> out_list;
	string block;
	while(getline(stream, block, delimiter))
	{
		out_list.push_back(block);
	}
	return  out_list;
}

vector<Song*> CommandHandler::tokenize_table(vector<vector<string>> table)
{
	vector<Song*> tokens;
	vector<string> header = table[0];
	for(int i = 1; i < table.size(); i++)
	{
		tokens.push_back(tokenize(table[i], header));
	}
	return tokens;
}

Song* CommandHandler::tokenize(vector<string> raw,vector<string> header)
{
	int id = stoi(raw[find_index_in_vector(header, ID)]);
	string title = raw[find_index_in_vector(header, TITLE)];
	string artist = raw[find_index_in_vector(header, ARTIST)];
	int release_year = stoi(raw[find_index_in_vector(header, RELEASE_YEAR)]);
	string link = raw[find_index_in_vector(header, LINK)];
	Song *new_song = new Song(id,title,artist,release_year,link);
	return new_song;
}

int CommandHandler::find_index_in_vector(const vector<string>& vec, string s)
{
	const int INVALID = -1;
	for(int i = 0; i < vec.size(); i++)
	{
		if(vec[i] == s)
			return i;
	}
	return INVALID;
}










