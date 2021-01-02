#include<iostream>
#include <string>
#include "src/CommandHandler.hpp"
#include "src/Utunes.hpp"
#include "src/web/RouteHandler.hpp"
using namespace std;
int main(int argc, char** argv)
{
	const int SONGS_INDEX = 1;
	const int LIKED_SONGS_INDEX = 2;
	char* songs_csv_file = argv[SONGS_INDEX];
	char* liked_songs_csv_file = argv[LIKED_SONGS_INDEX];
	CommandHandler command_handler = CommandHandler(songs_csv_file,liked_songs_csv_file);
	/* Uncomment this for CLI section*/
	//command_handler.run();

	/* Web */
	Utunes* utunes = command_handler.get_utunes();
	RouteHandler route_handler = RouteHandler(utunes);
	route_handler.run();
	return 0;
}