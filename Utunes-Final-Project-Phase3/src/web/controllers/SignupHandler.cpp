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
		utunes->create_new_user(email,username,password);
		res->setSessionId(email);
	}
	catch(std::exception& excep)
	{
		std::string message = excep.what();
		res = Response::redirect("/signup?error="+message);
	}
	return res;
}