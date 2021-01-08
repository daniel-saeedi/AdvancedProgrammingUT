#include "LikedSongController.hpp"

std::map<std::string,std::string> LikedSongController::handle(Request *req)
{
	std::map<std::string,std::string> context;
	if(req->getSessionId() != "")
	{
		User* user = utunes->find_user_by_email(req->getSessionId());
		context["logged_in"] = "true";
		context["liked_songs"] = liked_songs_html(user);
	}
	else context["logged_in"] = "false";
	return context;
}

std::string LikedSongController::liked_songs_html(User* user)
{
	std::vector<Song*> songs = utunes->get_liked_songs(user);
	std::string html;
	for(int i = 0;i < songs.size();i++)
		html += produce_row(songs[i]->get_id(),songs[i]->get_title(),songs[i]->get_artist(),songs[i]->get_year());
	return html;
}

std::string LikedSongController::produce_row(int id,std::string song,std::string artist,int year)
{
	std::string result = "<tr>";
	result += "<td>" + std::to_string(id) + "</td>";
	result += "<td><img class='thumbnail' style='border-radius:50%;' src='images/song.png' width='70'></td>";
	result += "<td><a href='song?id="+std::to_string(id)+"'>" + song + "</a></td>";
	result += "<td>" + artist + "</td>";
	result += "<td>" + std::to_string(year) + "</td></a>";
	result += "<td><a href='/like?id="+std::to_string(id)+"&operation=unlike'><img src='images/heart-red.png' width='30'> unlike</a></td></tr>";
	return result;
}