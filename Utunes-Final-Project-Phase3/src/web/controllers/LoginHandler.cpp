#include "LoginHandler.hpp"
Response* LoginHandler::callback(Request *req)
{
	Response* res = Response::redirect("/");
	if(req->getSessionId() != "") return res;
	string email = req->getBodyParam("email");
	string password = req->getBodyParam("password");
	try
	{
		utunes->login(email,password);
		res->setSessionId(email);
	}
	catch(std::exception& excep)
	{
		std::string message = excep.what();
		res = Response::redirect("/login?error="+message);
	}
	return res;
}