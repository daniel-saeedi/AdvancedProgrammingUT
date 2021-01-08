#ifndef LIKED_SONG_CONTROLLER_H
#define LIKED_SONG_CONTROLLER_H
#include <iostream>
#include <string>
#include <map>
#include "../../../server/server.hpp"
#include "../../Song.hpp"
#include "../../Utunes.hpp"
class LikedSongController : public TemplateHandler 
{
public:
	LikedSongController(std::string file_path,Utunes* _utunes) : TemplateHandler(file_path),utunes(_utunes){}
	std::map<std::string,std::string> handle(Request *req);
private:
	Utunes *utunes;
	std::string liked_songs_html(User* user);
	std::string produce_row(int id,std::string song,std::string artist,int year);
};
#endif