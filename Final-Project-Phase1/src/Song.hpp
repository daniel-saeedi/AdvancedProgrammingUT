#ifndef SONG_H
#define SONG_H
#include <iostream>
#include <string>
#include "LikeSystem.hpp"
#include "CommentSystem.hpp"
#include "User.hpp"
class Song : public LikeSystem, public CommentSystem
{
public:
	Song(int _id,std::string _title,std::string _artist,int _release_year,std::string _link)
		: id(_id), title(_title), artist(_artist), release_year(_release_year),link(_link) {}
	void print_info();
	void print_single_info();
	bool is_equal(int _id);
	bool is_artist_equal(std::string _artist);
	int get_year(){return release_year;};
	int get_id(){return id;}
private:
	int id;
	std::string title;
	std::string artist;
	int release_year;
	std::string link;
};
#endif