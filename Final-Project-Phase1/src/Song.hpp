#ifndef SONG_H
#define SONG_H
#include <iostream>
#include <string>
class Song
{
public:
	Song(int _id,std::string _title,std::string _artist,int _release_year,std::string _link)
		: id(_id), title(_title), artist(_artist), release_year(_release_year),link(_link){};
private:
	int id;
	std::string title;
	std::string artist;
	int release_year;
	std::string link;
};
#endif