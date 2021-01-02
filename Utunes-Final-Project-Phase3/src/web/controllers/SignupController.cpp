#include "SignupController.hpp"

std::map<std::string,std::string> SignupController::handle(Request *req)
{
	std::map<std::string,std::string> context;
	std::string error = req->getQueryParam("error");
	context["error"] = error;
	return context;
}

Response* SignupController::callback(Request* req)
{
	Response* res = Response::redirect("/");
	if(req->getSessionId() != "") return res;
	return nullptr;
}