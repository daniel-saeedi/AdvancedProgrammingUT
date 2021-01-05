#include "RemoveSongHandler.hpp"

Response* RemoveSongHandler::callback(Request *request)
{
	Response* res = Response::redirect("/");
	if(request->getSessionId() == "") return res;
	int playlist_id = stoi(request->getQueryParam("playlist_id"));
	int song_id = stoi(request->getQueryParam("song_id"));
	res = Response::redirect("/playlist?id="+std::to_string(playlist_id));
	try
	{
		Song* song = utunes->find_song_by_id(song_id);
		User* current_user = utunes->get_current_user();
		PlaylistSystem* playlist_sys = utunes->get_playlist_sys();
		playlist_sys->delete_song(playlist_id,song,current_user);
	}
	catch(std::exception& excep)
	{
		std::string message = excep.what();
		res = Response::redirect("/?error="+message);
	}
	return res;
}