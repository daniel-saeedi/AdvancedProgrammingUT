#include "Session.hpp"

Session::Session(User *_user)
{
	user = _user;
	songs_filter_status = false;
}

bool Session::is_songs_filtered()
{
	return songs_filter_status;
}
void Session::show_songs()
{
	for(int i = 0;i < filtered_songs.size();i++)
	{
		filtered_songs[i]->print_info();
	}
}