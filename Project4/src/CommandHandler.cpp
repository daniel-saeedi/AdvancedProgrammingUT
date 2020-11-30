#include "CommandHandler.hpp"
#include "Exception/GameNotCreatedException.hpp"
constexpr char CREATE_GAME[] = "create_game";
constexpr char ASSIGN_ROLE[] = "assign_role";
constexpr char START_GAME[] = "start_game";

CommandHandler::CommandHandler(){game = nullptr;}

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
				if(command_type == CREATE_GAME)
				{
					create_game(tokenized_input);
				}
				else if(command_type == ASSIGN_ROLE)
				{
					assign_role(tokenized_input);
				}
				else if(command_type == START_GAME)
				{
					start_game();
				}
			}
			catch(const exception& error)
			{
				cerr << error.what();
			}
		}
	}
}

void CommandHandler::create_game(vector<string> tokenized_input)
{
	const int FIRST_PLAYER_INDEX = 1;
	game = new Game();
	for(int i = FIRST_PLAYER_INDEX;i < tokenized_input.size();i++)
	{
		game->add_unassgined_player(tokenized_input[i]);
	}
}

void CommandHandler::assign_role(vector<string> tokenized_input)
{
	if(game == nullptr) throw GameNotCreatedException();
	const int PLAYER_NAME_INDEX = 1;
	const int PLAYER_ROLE_INDEX = 2;
	game->assign_role(tokenized_input[PLAYER_NAME_INDEX],tokenized_input[PLAYER_ROLE_INDEX]);	
}

void CommandHandler::start_game()
{
	if(game == nullptr) throw GameNotCreatedException();
	game->start_game();
}

vector<string> CommandHandler::tokenize_input(string input)
{
	stringstream input_string_stream(input);
	return vector<string>(istream_iterator<string>(input_string_stream),istream_iterator<string>());
}
















