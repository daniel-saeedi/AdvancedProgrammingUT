#include "PlaylistsController.hpp"

std::map<std::string,std::string> PlaylistsController::handle(Request *req)
{
	std::map<std::string,std::string> context;
	if(req->getSessionId() != "")
	{
		context["logged_in"] = "true";
		User* user = utunes->find_user_by_email(req->getSessionId());
		context["playlists"] = get_playlists(user);
	}
	else context["logged_in"] = "false";
	return context;
}

std::string PlaylistsController::get_playlists(User* current_user)
{
	PlaylistSystem* playlist_sys = utunes->get_playlist_sys();
	vector<Playlist*> playlists = playlist_sys->get_playlists(current_user);
	std::string html;
	for(int i = 0;i < playlists.size();i++)
	{
		if(playlists[i]->is_private() && !playlists[i]->is_user_equal(current_user)) continue;
		html += produce_row(playlists[i]->get_id(),playlists[i]->get_name(),playlists[i]->is_private(),playlists[i]->get_user_name());
	}
	return html;
}

std::string PlaylistsController::produce_row(int id,std::string title,bool privacy,std::string username)
{
	std::string result = "<tr>";
	result += "<td>" + std::to_string(id) + "</td>";
	result += "<td>" + title + "</td>";
	if(privacy)
		result += "<td>Private</td>";
	else
		result += "<td>Public</td>";
	result += "<td>"+ username +"</td>";
	result += "<td><a href='/playlist?id="+ std::to_string(id) +"'>Manage</a></td></tr>";
	return result;
}