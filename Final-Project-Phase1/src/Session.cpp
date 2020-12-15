#include "Session.hpp"
#include "Exception/EmptyException.hpp"

Session::Session(User *_user)
{
	user = _user;
	songs_filter_status = false;
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
	if(filtered_songs.size() == 0) throw EmptyException();
	for(int i = 0;i < filtered_songs.size();i++)
	{
		filtered_songs[i]->print_info();
	}
}

void Session::add_artist_filter(std::string artist)
{
	songs_filter_status = true;
	//remove_filter(ARTIST_INDEX);
	filters.push_back(new ArtistCriteria(artist));
}

void Session::add_public_year_filter(int min,int max)
{
	songs_filter_status = true;
	//remove_filter(PUBLISH_YEAR_INDEX);
	filters.push_back(new PublishYearCriteria(min,max));
}

void Session::add_likes_filter(int min,int max)
{
	songs_filter_status = true;
	//remove_filter(LIKE_INDEX);
	filters.push_back(new LikesCriteria(min,max));
}

void Session::remove_filter(int index)
{
	if(filters[index] != nullptr)
	{
		filters[index] = nullptr;
		Criteria *previous = filters[index];
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