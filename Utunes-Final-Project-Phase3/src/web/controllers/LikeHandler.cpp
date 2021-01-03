#include "LikeHandler.hpp"
Response* LikeHandler::callback(Request *req)
{
	Response* res = Response::redirect("/");
	if(req->getSessionId() == "") return res;
	int id = stoi(req->getQueryParam("id"));
	std::string operation = req->getQueryParam("operation");
	res = Response::redirect("/song?id="+std::to_string(id));
	try
	{
		if(operation == "like")
			utunes->new_like(id);
		else if(operation == "unlike")
			utunes->delete_like(id);
	}
	catch(std::exception& excep)
	{
		std::string message = excep.what();
		res = Response::redirect("/login?error="+message);
	}
	return res;
}