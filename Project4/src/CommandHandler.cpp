#include "CommandHandler.hpp"
#include "Exception/GameNotCreatedException.hpp"
constexpr char CREATE_GAME[] = "create_game";
constexpr char ASSIGN_ROLE[] = "assign_role";
constexpr char START_GAME[] = "start_game";
constexpr char END_VOTE[] = "end_vote";
constexpr char END_NIGHT[] = "end_night";
constexpr char GET_GAME_STATE[] = "get_game_state";
constexpr char SWAP_CHARACTER[] = "swap_character";

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
				if(game == nullptr)
				{
					day_command(command_type,tokenized_input);
				}
				else
				{
					if(command_type == SWAP_CHARACTER)
					{
						swap_character(tokenized_input);
					}
					if(command_type == GET_GAME_STATE)
					{
						game->get_game_state();
					}
					else if(!game->is_finished())
					{
						if(game->get_is_night()) night_command(command_type,tokenized_input);
						else day_command(command_type,tokenized_input);
					}
				}
			}
			catch(const exception& error)
			{
				//cerr << error.what();
				cout << error.what();
			}
		}
	}
}

void CommandHandler::swap_character(vector<string> tokenized_input)
{
	const int PLAYER1_INDEX = 1;
	const int PLAYER2_INDEX = 2;
	game->swap_character(tokenized_input[PLAYER1_INDEX],tokenized_input[PLAYER2_INDEX]);
}

void CommandHandler::day_command(string command_type,vector<string> tokenized_input)
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
	else if(command_type == END_VOTE)
	{
		game->end_vote();
	}
	else if(tokenized_input.size() == 2)
	{
		day_vote(tokenized_input);
	}
}

void CommandHandler::night_command(string command_type,vector<string> tokenized_input)
{
	if(command_type == END_NIGHT)
	{
		game->end_night();
	}
	else if(tokenized_input.size() == 2)
	{
		const int VOTER_INDEX = 0;
		const int VOTEE_INDEX = 1;
		game->night_events(tokenized_input[VOTER_INDEX],tokenized_input[VOTEE_INDEX]);
	}
}

void CommandHandler::day_vote(vector<string> tokenized_input)
{
	const int VOTER_INDEX = 0;
	const int VOTEE_INDEX = 1;
	game->vote(tokenized_input[VOTER_INDEX],tokenized_input[VOTEE_INDEX]);
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
















