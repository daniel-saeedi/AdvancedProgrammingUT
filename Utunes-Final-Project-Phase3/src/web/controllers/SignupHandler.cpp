#include "SignupHandler.hpp"
#include <exception>
Response* SignupHandler::callback(Request* req)
{
	Response* res = Response::redirect("/");
	if(req->getSessionId() != "") return res;
	string email = req->getBodyParam("email");
	string username = req->getBodyParam("username");
	string password = req->getBodyParam("password");
	try
	{
		utunes->signup(email,username,password);
	}
	catch(std::exception& excep)
	{
		std::string message = excep.what();
		res = Response::redirect("/signup?error="+message);
	}
	res->setSessionId(username);
	return res;
}