#include <algorithm>
#include "Session.hpp"
#include "Exception/EmptyException.hpp"

bool song_compare_by_id(Song *song1,Song *song2)
{
	return song1->get_id() < song2->get_id();
}

Session::Session(User *_user)
{
	user = _user;
	songs_filter_status = false;
	for(int i = 0;i < FILTERS_SIZE;i++)
	{
		filters.push_back(nullptr);
	}
}

Session::~Session()
{
	for(int i = 0;i < filters.size();i++)
		delete filters[i];
}

bool Session::is_songs_filtered()
{
	return songs_filter_status;
}

void Session::show_songs(std::vector<Song*> songs)
{
	AndCriteria *and_criteria = new AndCriteria(filters);
	std::vector<Song*> filtered_songs = and_criteria->meet_criteria(songs);
	delete and_criteria;
	sort(filtered_songs.begin(),filtered_songs.end(),song_compare_by_id);
	if(filtered_songs.size() == 0) throw EmptyException();
	for(int i = 0;i < filtered_songs.size();i++)
	{
		filtered_songs[i]->print_info();
	}
}

std::vector<Song*> Session::get_filtered_songs(std::vector<Song*> songs)
{
	AndCriteria *and_criteria = new AndCriteria(filters);
	std::vector<Song*> filtered_songs = and_criteria->meet_criteria(songs);
	delete and_criteria;
	if(filters.size() == 0)
		return songs;
	else
		return filtered_songs;
}

void Session::add_artist_filter(std::string artist)
{
	songs_filter_status = true;
	remove_filter(ARTIST_INDEX);
	filters[ARTIST_INDEX] = new ArtistCriteria(artist);
}

void Session::add_public_year_filter(int min,int max)
{
	songs_filter_status = true;
	if(min <= max) remove_filter(PUBLISH_YEAR_INDEX);
	filters[PUBLISH_YEAR_INDEX] = new PublishYearCriteria(min,max);
}

void Session::add_likes_filter(int min,int max)
{
	songs_filter_status = true;
	if(min <= max ) remove_filter(PUBLISH_YEAR_INDEX);
	filters[LIKE_INDEX] = new LikesCriteria(min,max);
}

void Session::remove_filter(int index)
{
	if(filters[index] != nullptr)
	{
		Criteria *previous = filters[index];
		filters[index] = nullptr;
		delete previous;
	}
}

void Session::delete_filters()
{
	songs_filter_status = false;
	for(int i = 0;i < filters.size();i++)
	{
		remove_filter(i);
	}
}