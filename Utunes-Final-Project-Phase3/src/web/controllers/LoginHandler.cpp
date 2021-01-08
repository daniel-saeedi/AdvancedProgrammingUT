#include "LoginHandler.hpp"
Response* LoginHandler::callback(Request *req)
{
	Response* res = Response::redirect("/");
	if(req->getSessionId() != "") return res;
	string email = req->getBodyParam("email");
	string password = req->getBodyParam("password");
	if(utunes->users_exists(email,password))
	{
		res->setSessionId(email);
	}
	else
	{
		std::string message = "Bad Request";
		res = Response::redirect("/login?error="+message);
	}
	return res;
}