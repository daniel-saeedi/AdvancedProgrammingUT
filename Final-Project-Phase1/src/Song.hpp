#ifndef SONG_H
#define SONG_H
#include <iostream>
#include <string>
#include "LikeSystem.hpp"
#include "CommentSystem.hpp"
#include "User.hpp"
class Song
{
public:
	Song(int _id,std::string _title,std::string _artist,int _release_year,std::string _link)
		: id(_id), title(_title), artist(_artist), release_year(_release_year),link(_link)
	{
		like_sys = new LikeSystem;
		comment_sys = new CommentSystem;
	};
	void print_info();
	void print_single_info();
	bool is_equal(int _id);
	bool has_liked(User *user);
	void like(User *user);
	void delete_like(User *user);
	void add_comment(User *user,int time,std::string comment);
	void get_comments();
private:
	int id;
	std::string title;
	std::string artist;
	int release_year;
	std::string link;
	LikeSystem *like_sys;
	CommentSystem *comment_sys;
};
#endif