#include "CommandHandler.hpp"
const char CSV_DELIMITER = ',';
//Headers
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

			}
			catch(const exception& error)
			{
				cerr << error.what();
			}
		}
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










