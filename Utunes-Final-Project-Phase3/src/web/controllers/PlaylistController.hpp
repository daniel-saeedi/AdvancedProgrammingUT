#ifndef PLAYLIST_CONTROLLER_H
#define PLAYLIST_CONTROLLER_H
#include <iostream>
#include <string>
#include <map>
#include "../../../server/server.hpp"
#include "../../Song.hpp"
#include "../../Utunes.hpp"
#include "../../Playlist.hpp"
#include "../../PlaylistSystem.hpp"
class PlaylistController : public TemplateHandler 
{
public:
	PlaylistController(std::string file_path,Utunes* _utunes) : TemplateHandler(file_path),utunes(_utunes){}
	std::map<std::string,std::string> handle(Request *req);
private:
	Utunes *utunes;
	std::map<std::string,std::string> get_info(Request* req);
	std::string songs_html(int playlist_id,vector<Song*> songs,bool can_delete);
	std::string produce_row(int playlist_id,int id,std::string song,std::string artist,int year,bool can_delete);
};
#endif