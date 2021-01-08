#include "FilterSystem.hpp"
#include <algorithm>
#include "Exception/EmptyException.hpp"
const int ARTIST_INDEX_ = 0;
const int PUBLISH_YEAR_INDEX_ = 1;
const int LIKE_INDEX_ = 2;
const int FILTERS_SIZE_ = 3;

FilterSystem::FilterSystem(User *_user)
{
	user = _user;
	for(int i = 0;i < FILTERS_SIZE_;i++)
	{
		filters.push_back(nullptr);
	}
}

FilterSystem::~FilterSystem()
{
	for(int i = 0;i < filters.size();i++)
		delete filters[i];
}

std::vector<Song*> FilterSystem::get_filtered_songs(std::vector<Song*> songs)
{
	AndCriteria *and_criteria = new AndCriteria(filters);
	std::vector<Song*> filtered_songs = and_criteria->meet_criteria(songs);
	delete and_criteria;
	if(filters.size() == 0)
		return songs;
	else
		return filtered_songs;
}

void FilterSystem::add_artist_filter(std::string artist)
{
	remove_filter(ARTIST_INDEX_);
	filters[ARTIST_INDEX_] = new ArtistCriteria(artist);
}

void FilterSystem::add_publish_year_filter(int min,int max)
{
	if(min <= max) remove_filter(PUBLISH_YEAR_INDEX_);
	filters[PUBLISH_YEAR_INDEX_] = new PublishYearCriteria(min,max);
}

void FilterSystem::add_likes_filter(int min,int max)
{
	if(min <= max ) remove_filter(PUBLISH_YEAR_INDEX_);
	filters[LIKE_INDEX_] = new LikesCriteria(min,max);
}

void FilterSystem::remove_filter(int index)
{
	if(filters[index] != nullptr)
	{
		Criteria *previous = filters[index];
		filters[index] = nullptr;
		delete previous;
	}
}

void FilterSystem::delete_filters()
{
	for(int i = 0;i < filters.size();i++)
	{
		remove_filter(i);
	}
}