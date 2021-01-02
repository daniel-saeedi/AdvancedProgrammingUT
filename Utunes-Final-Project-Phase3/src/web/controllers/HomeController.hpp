#ifndef HOME_CONTROLLER_H
#define HOME_CONTROLLER_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "../../../server/server.hpp"
#include "../../Song.hpp"
class HomeController : public TemplateHandler
{
public:
	HomeController(std::string file_path,std::vector<Song*> _songs,int _users_count) : TemplateHandler(file_path),songs(_songs),users_count(_users_count){};
	std::map<std::string,std::string> handle(Request *req);
private:
	std::vector<Song*> songs;
	std::string produce_row(int id,std::string song,std::string artist,int year);
	int users_count;
};
#endif