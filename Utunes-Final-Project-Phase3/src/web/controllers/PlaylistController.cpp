#include "PlaylistController.hpp"
const int DEFAULT_ID = 1;

std::map<std::string,std::string> PlaylistController::handle(Request* req)
{
	std::map<std::string,std::string> context;
	if(req->getSessionId() != "")
	{
		context = get_info(req);
	}
	else context["logged_in"] = "false";
	return context;
}

std::map<std::string,std::string> PlaylistController::get_info(Request* req)
{
	std::map<std::string,std::string> context;
	int id = DEFAULT_ID;
	if(req->getQueryParam("id") != "") id = stoi(req->getQueryParam("id"));
	PlaylistSystem* playlist_sys = utunes->get_playlist_sys();
	User* current_user = utunes->get_current_user();
	Playlist* playlist = playlist_sys->get_playlist_by_index(id,current_user);
	bool can_delete = true;
	if(!playlist->is_user_equal(current_user))
	{
		context["can_add"] = "false";
		can_delete = false;
	}
	else
		context["can_add"] = "true";
	if(playlist->is_private())
		context["title"] = playlist->get_name() + "(Private)";
	else
		context["title"] = playlist->get_name() + "(Public)";
	context["songs"] = songs_html(id,playlist->get_songs(),can_delete);
	context["playlist_id"] = std::to_string(id);
	context["playlist_name"] = playlist->get_name();
	context["logged_in"] = "true";
	return context;
}

std::string PlaylistController::songs_html(int playlist_id,vector<Song*> songs,bool can_delete)
{
	std::string html;
	for(int i = 0;i < songs.size();i++)
		html += produce_row(playlist_id,songs[i]->get_id(),songs[i]->get_title(),songs[i]->get_artist(),songs[i]->get_year(),can_delete);
	return html;
}

std::string PlaylistController::produce_row(int playlist_id,int id,std::string song,std::string artist,int year,bool can_delete)
{
	std::string result = "<tr>";
	result += "<td>" + std::to_string(id) + "</td>";
	result += "<td><img class='thumbnail' style='border-radius:50%;' src='images/song.png' width='70'></td>";
	result += "<td><a href='song?id="+std::to_string(id)+"'>" + song + "</a></td>";
	result += "<td>" + artist + "</td>";
	result += "<td>" + std::to_string(year) + "</td></a>";
	result += "<td>";
	if(can_delete)
		result += "<a href='/delete_song?song_id="+std::to_string(id)+"&playlist_id="+std::to_string(playlist_id)+"'><img src='images/delete-red.png' width='30'></a>";
	result += "</td></tr>";
	return result;
}