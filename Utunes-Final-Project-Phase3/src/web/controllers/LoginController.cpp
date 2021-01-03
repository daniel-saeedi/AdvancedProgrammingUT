#include "LoginController.hpp"

std::map<std::string,std::string> LoginController::handle(Request *req)
{
	std::map<std::string,std::string> context;
	std::string error = req->getQueryParam("error");
	context["error"] = error;
	if(req->getSessionId() != "") context["logged_in"] = "true";
	else context["logged_in"] = "false";
	return context;
}