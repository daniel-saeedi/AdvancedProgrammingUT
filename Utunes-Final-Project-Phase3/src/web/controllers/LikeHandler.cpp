#include "LikeHandler.hpp"
Response* LikeHandler::callback(Request *req)
{
	Response* res = Response::redirect("/");
	if(req->getSessionId() == "") return res;
	try
	{
		int id = stoi(req->getQueryParam("id"));
		std::string operation = req->getQueryParam("operation");
		res = Response::redirect("/song?id="+std::to_string(id));
		User* user = utunes->find_user_by_email(req->getSessionId());
		if(operation == "like")
			utunes->new_like(id,user);
		else if(operation == "unlike")
			utunes->delete_like(id,user);
	}
	catch(std::exception& excep)
	{
		std::string message = excep.what();
		res = Response::redirect("/?error="+message);
	}
	return res;
}