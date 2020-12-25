#include<iostream>
#include <string>
#include "src/CommandHandler.hpp"
using namespace std;
int main(int argc, char** argv)
{
	const int SONGS_INDEX = 1;
	const int LIKED_SONGS_INDEX = 2;
	char* songs_csv_file = argv[SONGS_INDEX];
	char* liked_songs_csv_file = argv[LIKED_SONGS_INDEX];
	CommandHandler command_handler = CommandHandler(songs_csv_file,liked_songs_csv_file);
	command_handler.run();
	return 0;
}