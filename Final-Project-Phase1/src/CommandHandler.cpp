#include <map>
#include "CommandHandler.hpp"
#include "Exception/BadRequestException.hpp"
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
constexpr char EMAIL[] = "email";
constexpr char USERNAME[] = "username";
constexpr char PASSWORD[] = "password";
constexpr char MIN_YEAR[] = "min_year";
constexpr char MAX_YEAR[] = "max_year";
constexpr char MIN_LIKE[] = "min_like";
constexpr char MAX_LIKE[] = "max_like";
constexpr char PRIVATE[] = "private";
constexpr char PUBLIC[] = "public";
constexpr char NAME[] = "name";
constexpr char PRIVACY[] = "privacy";
constexpr char PLAYLIST_ID[] = "playlist_id";
constexpr char SONG_ID[] = "song_id";
constexpr char TIME[] = "time";
constexpr char COMMENT[] = "comment";
constexpr int OPERATION_INDEX = 1;
constexpr int QUESTION_MARK_INDEX = 3;
constexpr int MIN_TOKENS = 2;
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

CommandHandler::~CommandHandler()
{
	delete utunes;
}

void CommandHandler::run()
{
	const int COMMAND_TYPE_INDEX = 0;
	string input;
	while (getline(cin,input))
	{
		if(input != "")
		{
			vector<string> tokenized_input = tokenize_input(input);
			const string command_type = tokenized_input[COMMAND_TYPE_INDEX];
			try
			{
				if(command_type == POST) 
					post_commands(tokenized_input);
				else if(command_type == GET) 
					get_commands(tokenized_input);
				else if(command_type == DELETE) 
					delete_commands(tokenized_input);
				else
					throw BadRequestException();
			}
			catch(const exception& error)
			{
				cout << error.what();
			}
		}
	}
}

void CommandHandler::post_commands(vector<string> tokenized_input)
{
	string operation = tokenized_input[OPERATION_INDEX];
	if(tokenized_input.size() > MIN_TOKENS)
		tokenized_input.erase(tokenized_input.begin(),tokenized_input.begin() + QUESTION_MARK_INDEX);
	if(operation == SINGUP)
		signup(tokenized_input);
	else if(operation == LOGIN)
		login(tokenized_input);
	else if(operation == LOGOUT)
		utunes->logout();
	else if(operation == LIKES)
		new_like(tokenized_input);
	else if(operation == PLAYLISTS)
		add_playlist(tokenized_input);
	else if(operation == PLAYLISTS_SONGS)
		add_song_to_playlist(tokenized_input);
	else if(operation == COMMENTS)
		add_comment(tokenized_input);
	else if(operation == FILTERS)
		add_filter(tokenized_input);
	else
		throw BadRequestException();
}

void CommandHandler::get_commands(vector<string> tokenized_input)
{
	string operation = tokenized_input[OPERATION_INDEX];
	if(operation == SONGS)
	{
		if(tokenized_input.size() == MIN_TOKENS) utunes->get_songs();
		else
		{
			tokenized_input.erase(tokenized_input.begin(),tokenized_input.begin() + QUESTION_MARK_INDEX);
			get_song(tokenized_input);
		}
	}
	else
	{
		if(tokenized_input.size() > MIN_TOKENS)
			tokenized_input.erase(tokenized_input.begin(),tokenized_input.begin() + QUESTION_MARK_INDEX);
		if(operation == LIKES) 
			utunes->show_likes();
		else if(operation == PLAYLISTS) 
			get_playlists(tokenized_input);
		else if(operation == PLAYLISTS_SONGS) 
			get_playlist_songs(tokenized_input);
		else if(operation == USERS) 
			utunes->get_users();
		else if(operation == COMMENTS) 
			get_comments(tokenized_input);
		else
			throw BadRequestException();
	}
	
}

void CommandHandler::delete_commands(vector<string> tokenized_input)
{
	string operation = tokenized_input[OPERATION_INDEX];
	if(tokenized_input.size() > MIN_TOKENS)
		tokenized_input.erase(tokenized_input.begin(),tokenized_input.begin() + QUESTION_MARK_INDEX);
	if(operation == LIKES)
		delete_like(tokenized_input);
	else if(operation == PLAYLISTS_SONGS)
		delete_playlist_song(tokenized_input);
	else if(operation == FILTERS)
		utunes->delete_filters();
	else
		throw BadRequestException();
}


void CommandHandler::signup(vector<string> info)
{
	vector<string> headers = {EMAIL,USERNAME,PASSWORD};
	is_command_valid(info.size(),headers.size());
	map<string,string> data = split_by_headers(headers,info);
	string email = data[EMAIL];
	string username = data[USERNAME];
	string password = data[PASSWORD];
	utunes->signup(email,username,password);
}

void CommandHandler::login(vector<string> info)
{
	vector<string> headers = {EMAIL,PASSWORD};
	is_command_valid(info.size(),headers.size());
	map<string,string> data = split_by_headers(headers,info);
	string email = data[EMAIL];
	string password = data[PASSWORD];
	utunes->login(email,password);
}

void CommandHandler::new_like(vector<string> info)
{
	utunes->check_login();
	vector<string> headers = {ID};
	is_command_valid(info.size(),headers.size());
	map<string,string> data = split_by_headers(headers,info);
	int id = stoi(data[ID]);
	utunes->new_like(id);
}

void CommandHandler::add_playlist(vector<string> info)
{
	utunes->check_login();
	vector<string> headers = {NAME,PRIVACY};
	is_command_valid(info.size(),headers.size());
	map<string,string> data = split_by_headers(headers,info);
	string name = data[NAME];
	bool private_status;
	if(data[PRIVACY] == PRIVATE) private_status = true;
	if(data[PRIVACY] == PUBLIC) private_status = false;
	utunes->add_playlist(name,private_status);
}

void CommandHandler::add_song_to_playlist(vector<string> info)
{
	utunes->check_login();
	vector<string> headers = {PLAYLIST_ID,SONG_ID};
	is_command_valid(info.size(),headers.size());
	map<string,string> data = split_by_headers(headers,info);
	int playlist_id = stoi(data[PLAYLIST_ID]);
	int song_id = stoi(data[SONG_ID]);
	utunes->add_song_to_playlist(playlist_id,song_id);
}

void CommandHandler::add_comment(vector<string> info)
{
	utunes->check_login();
	vector<string> headers = {SONG_ID,TIME,COMMENT};
	is_command_valid(info.size(),headers.size());
	map<string,string> data = split_by_headers(headers,info);
	int song_id = stoi(data[SONG_ID]);
	int time = stoi(data[TIME]);
	string comment = data[COMMENT];
	utunes->add_comment(song_id,time,comment);
}

void CommandHandler::add_filter(vector<string> info)
{
	utunes->check_login();
	string operation = info[0];
	if(operation == ARTIST) add_artist_filter(info);
	else if(operation == MIN_YEAR) add_publish_year_filter(info);
	else if(operation == MIN_LIKE) add_likes_filter(info);
	else throw BadRequestException();
}

void CommandHandler::add_artist_filter(vector<string> info)
{
	if(info.size() < MIN_TOKENS) throw BadRequestException();
	const int INVAL = -1;
	string artist;
	int name_index = INVAL;
	for(int i = 0;i < info.size();i++)
	{
		if(name_index != INVAL)
		{
			artist += info[i];
			if(i < info.size() - 1) artist += " ";
		}
		if(info[i] == ARTIST) name_index = i + 1;
	}
	utunes->add_artist_filter(artist);
}

void CommandHandler::add_publish_year_filter(vector<string> info)
{
	vector<string> headers = {MIN_YEAR,MAX_YEAR};
	is_command_valid(info.size(),headers.size());
	map<string,string> data = split_by_headers(headers,info);
	int min_year = stoi(data[MIN_YEAR]);
	int max_year = stoi(data[MAX_YEAR]);
	utunes->add_publish_year_filter(min_year,max_year);
}

void CommandHandler::add_likes_filter(vector<string> info)
{
	vector<string> headers = {MIN_LIKE,MAX_LIKE};
	is_command_valid(info.size(),headers.size());
	map<string,string> data = split_by_headers(headers,info);
	int min_like = stoi(data[MIN_LIKE]);
	int max_like = stoi(data[MAX_LIKE]);
	utunes->add_likes_filter(min_like,max_like);
}

void CommandHandler::get_song(vector<string> info)
{
	vector<string> headers = {ID};
	is_command_valid(info.size(),headers.size());
	map<string,string> data = split_by_headers(headers,info);
	int id = stoi(data[ID]);
	utunes->get_song(id);
}

void CommandHandler::get_playlists(vector<string> info)
{
	vector<string> headers = {USERNAME};
	is_command_valid(info.size(),headers.size());
	map<string,string> data = split_by_headers(headers,info);
	string username = data[USERNAME];
	utunes->get_playlists(username);
}

void CommandHandler::get_playlist_songs(vector<string> info)
{
	vector<string> headers = {PLAYLIST_ID};
	is_command_valid(info.size(),headers.size());
	map<string,string> data = split_by_headers(headers,info);
	int playlist_id = stoi(data[PLAYLIST_ID]);
	utunes->get_playlist_songs(playlist_id);
}

void CommandHandler::get_comments(vector<string> info)
{
	vector<string> headers = {SONG_ID};
	is_command_valid(info.size(),headers.size());
	map<string,string> data = split_by_headers(headers,info);
	int song_id = stoi(data[SONG_ID]);
	utunes->get_comments(song_id);
}

void CommandHandler::delete_like(vector<string> info)
{
	vector<string> headers = {ID};
	is_command_valid(info.size(),headers.size());
	map<string,string> data = split_by_headers(headers,info);
	int id = stoi(data[ID]);
	utunes->delete_like(id);
}

void CommandHandler::delete_playlist_song(vector<string> info)
{
	vector<string> headers = {PLAYLIST_ID,SONG_ID};
	is_command_valid(info.size(),headers.size());
	map<string,string> data = split_by_headers(headers,info);
	int playlist_id = stoi(data[PLAYLIST_ID]);
	int song_id = stoi(data[SONG_ID]);
	utunes->delete_playlist_song(playlist_id,song_id);
}

void CommandHandler::is_command_valid(int info_size,int headers_size)
{
	if(info_size != 2 * headers_size) throw BadRequestException();
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
    fin.open(file,ios::in);
    vector<vector<string>> table;
    while(getline(fin,line))
    {
		table.push_back(split(line,CSV_DELIMITER));
    }
    return table;
}

vector<string> CommandHandler::split(string line,char delimiter)
{
	stringstream stream(line);
	vector<string> out_list;
	string block;
	while(getline(stream,block,delimiter))
	{
		out_list.push_back(block);
	}
	return out_list;
}

vector<Song*> CommandHandler::tokenize_table(vector<vector<string>> table)
{
	vector<Song*> tokens;
	vector<string> header = table[0];
	for(int i = 1; i < table.size(); i++)
	{
		tokens.push_back(tokenize(table[i],header));
	}
	return tokens;
}

Song* CommandHandler::tokenize(vector<string> raw,vector<string> header)
{
	int id = stoi(raw[find_index_in_vector(header,ID)]);
	string title = raw[find_index_in_vector(header,TITLE)];
	string artist = raw[find_index_in_vector(header,ARTIST)];
	int release_year = stoi(raw[find_index_in_vector(header,RELEASE_YEAR)]);
	string link = raw[find_index_in_vector(header,LINK)];
	Song *new_song = new Song(id,title,artist,release_year,link);
	return new_song;
}

int CommandHandler::find_index_in_vector(const vector<string>& vec,string s)
{
	const int INVALID = -1;
	for(int i = 0; i < vec.size(); i++)
	{
		if(vec[i] == s)
			return i;
	}
	return INVALID;
}

map<string,string> CommandHandler::split_by_headers(vector<string> headers,vector<string> info)
{
	map<string,string> result;
	for(int i = 0;i < headers.size();i++)
	{
		for(int j = 0;j < info.size();j++)
		{
			if(headers[i] == info[j]) result[headers[i]] = info[j+1];
		}
	}
	if(result.size() != headers.size()) throw BadRequestException();
	return result;
}