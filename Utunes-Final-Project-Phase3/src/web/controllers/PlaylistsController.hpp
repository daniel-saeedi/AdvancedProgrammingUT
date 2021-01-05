#ifndef PLAYLISTS_CONTROLLER_H
#define PLAYLISTS_CONTROLLER_H
#include <iostream>
#include <string>
#include <map>
#include "../../../server/server.hpp"
#include "../../Song.hpp"
#include "../../Utunes.hpp"
class PlaylistsController : public TemplateHandler 
{
public:
	PlaylistsController(std::string file_path,Utunes* _utunes) : TemplateHandler(file_path),utunes(_utunes){}
	std::map<std::string,std::string> handle(Request *req);
private:
	Utunes *utunes;
	std::string get_playlists();
	std::string produce_row(int id,std::string title,bool privacy,std::string username);
};
#endif