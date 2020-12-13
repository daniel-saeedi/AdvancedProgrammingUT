#include "CommandHandler.hpp"
#include <iterator>

CommandHandler::CommandHandler()
{
	
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













