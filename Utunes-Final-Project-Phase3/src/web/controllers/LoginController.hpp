#ifndef LOGIN_CONTROLLER_H
#define LOGIN_CONTROLLER_H
#include <iostream>
#include <string>
#include <map>
#include "../../../server/server.hpp"
#include "../../User.hpp"
class LoginController : public TemplateHandler 
{
public:
	LoginController(std::string file_path) : TemplateHandler(file_path){}
	std::map<std::string,std::string> handle(Request *req);
private:
};
#endif