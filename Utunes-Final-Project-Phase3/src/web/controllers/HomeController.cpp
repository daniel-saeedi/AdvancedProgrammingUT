#include "HomeController.hpp"

std::map<std::string,std::string> HomeController::handle(Request *req)
{
	std::vector<Song*> songs = utunes->get_songs_vector();
	int users_count =  utunes->get_users_count();
	std::map<std::string,std::string> context;
	std::string rows;
	for(int i = 0;i < songs.size();i++)
	{
		rows += produce_row(songs[i]->get_id(),songs[i]->get_title(),songs[i]->get_artist(),songs[i]->get_year());
	}
	context["songs"] = rows;
	context["songs_count"] = std::to_string(songs.size()); 
	context["users_count"] = std::to_string(users_count);
	if(req->getSessionId() != "") context["logged_in"] = req->getSessionId();
	else context["logged_in"] = "false";
	return context;
}

std::string HomeController::produce_row(int id,std::string song,std::string artist,int year)
{
	std::string result = "<tr>";
	result += "<td>" + std::to_string(id) + "</td>";
	result += "<td><img class='thumbnail' src='images/person_1.jpg' width='70'></td>";
	result += "<td><a href='song?id="+std::to_string(id)+"'>" + song + "</a></td>";
	result += "<td>" + artist + "</td>";
	result += "<td>" + std::to_string(year) + "</td></a></tr>";
	return result;
}