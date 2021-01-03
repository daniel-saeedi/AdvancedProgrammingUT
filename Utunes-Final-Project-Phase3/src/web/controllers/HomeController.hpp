#ifndef HOME_CONTROLLER_H
#define HOME_CONTROLLER_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "../../../server/server.hpp"
#include "../../Song.hpp"
#include "../../Utunes.hpp"
class HomeController : public TemplateHandler
{
public:
	HomeController(std::string file_path,Utunes* _utunes) : TemplateHandler(file_path),utunes(_utunes){};
	std::map<std::string,std::string> handle(Request *req);
private:
	std::string produce_row(int id,std::string song,std::string artist,int year);
	Utunes* utunes;
};
#endif