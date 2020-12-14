#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "Song.hpp"
#include <iostream>
#include <vector>

class Playlist
{
public:
	Playlist(int _id,std::string _name,bool _private_status) 
		: id(_id), name(_name), private_status(_private_status) {}
private:
	int id;
	std::string name;
	bool private_status;
	std::vector<Song*> songs;
};
#endif