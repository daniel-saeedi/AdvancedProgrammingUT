#ifndef SIGNUP_CONTROLLER_H
#define SIGNUP_CONTROLLER_H
#include <iostream>
#include <string>
#include <map>
#include "../../../server/server.hpp"
#include "../../User.hpp"
#include "../../Utunes.hpp"
class SignupController : public TemplateHandler 
{
public:
	SignupController(std::string file_path,Utunes* _utunes) : TemplateHandler(file_path),utunes(_utunes){}
	std::map<std::string,std::string> handle(Request *req);
	Response* callback(Request *);
private:
	Utunes *utunes;
};
#endif