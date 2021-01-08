#include "LogoutHandler.hpp"
Response* LogoutHandler::callback(Request *request)
{
	Response* res = Response::redirect("/");
	res->setSessionId("");
	return res;
}