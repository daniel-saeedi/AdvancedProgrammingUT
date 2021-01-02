#include "LogoutHandler.hpp"
Response* LogoutHandler::callback(Request *request)
{
	Response* res = Response::redirect("/");
	try
	{
		res->setSessionId("");
		utunes->logout();
	}
	catch (exception& e)
	{
		std::string message = e.what();
	}
	return res;
}