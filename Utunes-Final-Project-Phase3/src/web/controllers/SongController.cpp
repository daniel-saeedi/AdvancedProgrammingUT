#include "SongController.hpp"


std::map<std::string,std::string> SongController::handle(Request *req)
{
	std::map<std::string,std::string> context;
	int id = 1;
	if(req->getQueryParam("id") != "") id = stoi(req->getQueryParam("id"));
	Song* song = utunes->find_song_by_id(id);
	context["id"] = id;
	context["title"] = song->get_title();
	context["artist"] = song->get_artist();
	context["link"] = song->get_link();
	context["year"] = std::to_string(song->get_year());
	context["likes"] = std::to_string(song->get_likes());
	context["playlists"] = std::to_string(utunes->get_playlist_sys()->count_playlists_contain_song(song));
	if(req->getSessionId() != "")
	{
		context["logged_in"] = "true";
		context["recommendation"] = get_recom(song);
		context["like_button"] = get_like_button(song);
	}
	else context["logged_in"] = "false";
	return context;
}

std::string SongController::get_like_button(Song* song)
{
	std::string html;
	if(song->has_liked(utunes->get_current_user()))
	{
		html += "<a href='/like?id="+std::to_string(song->get_id())+"&operation=unlike'><img src='images/heart-red.png' width='50'> unlike</a>";
	}
	else
	{
		html += "<a href='/like?id="+std::to_string(song->get_id())+"&operation=like'><img src='images/heart-null.png' width='50'> like</a>";
	}
	return html;
}

std::string SongController::get_recom(Song* current_song)
{
	std::vector<Song*> recommended = utunes->get_recommended_songs();
	std::string recom_html;
	int count = 1;
	for(int i = 0;i < recommended.size();i++)
	{
		if(count > 4) break;
		if(recommended[i] != current_song)
		{
			count++;
			recom_html += recommendation_html(recommended[i]->get_title(),recommended[i]->get_artist(),recommended[i]->get_id(),recommended[i]->get_year());
		}
	}
	return recom_html;
}
std::string SongController::recommendation_html(std::string title,std::string artist,int id,int year)
{
	std::string html = "<div class='block-21 mb-4 d-flex'><a class='blog-img mr-4' style='background-image: url(images/song.png);'></a><div class='text'><h3 class='heading'>";
	html += "<a href='/song?id="+std::to_string(id)+"'>"+title+"</a></h3>";
	html += "<div class='meta'><div><a href='#'><span class='icon-calendar'></span>" + std::to_string(year) + "</a></div>";
	html += "<div><a href='#'><span class='icon-calendar'></span>" + artist + "</a></div>";
	html += "</div></div></div>";
	return html;
}