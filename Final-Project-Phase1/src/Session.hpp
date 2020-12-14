#ifndef SESSION_H
#define SESSION_H
#include <iostream>
#include <vector>
#include "User.hpp"
#include "Song.hpp"
class Session
{
public:
	Session(User *_user);
	bool is_songs_filtered();
	void show_songs();
	User* get_user(){return user;}
private:
	User *user;
	bool songs_filter_status;
	std::vector<Song*> filtered_songs;
};
#endif