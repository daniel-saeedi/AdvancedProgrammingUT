#include<iostream>
#include <string>
#include "src/CommandHandler.hpp"
using namespace std;
int main(int argc, char** argv)
{
	const int FILENAME_INDEX = 1;
	char* csv_file = argv[FILENAME_INDEX];
	CommandHandler command_handler = CommandHandler(csv_file);
	command_handler.run();
	return 0;
}