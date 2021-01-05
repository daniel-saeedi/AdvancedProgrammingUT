#include "NewPlaylistHandler.hpp"
Response* NewPlaylistHandler::callback(Request *request)
{
	Response* res = Response::redirect("/");
	if(request->getSessionId() == "") return res;
	std::string name = request->getBodyParam("name");
	std::string privacy = request->getBodyParam("privacy");
	res = Response::redirect("/manage_playlists");
	try
	{
		bool is_private;
		if(privacy == "private")
			is_private = true;
		else
			is_private = false;
		utunes->add_playlist(name,is_private);
	}
	catch(std::exception& excep)
	{
		std::string message = excep.what();
		res = Response::redirect("/?error="+message);
	}
	return res;
}