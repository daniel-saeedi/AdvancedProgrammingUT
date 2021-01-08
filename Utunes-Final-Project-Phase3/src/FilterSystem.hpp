#ifndef FILTER_SYSTEM_H
#define FILTER_SYSTEM_H
#include <iostream>
#include <vector>
#include <map>
#include "User.hpp"
#include "Song.hpp"
#include "Criteria.hpp"
#include "ArtistCriteria.hpp"
#include "PublishYearCriteria.hpp"
#include "LikesCriteria.hpp"
#include "AndCriteria.hpp"
class FilterSystem
{
public:
	FilterSystem(User *_user);
	~FilterSystem();
	void add_artist_filter(std::string artist);
	void add_publish_year_filter(int min,int max);
	void add_likes_filter(int min,int max);
	void delete_filters();
	std::vector<Song*> get_filtered_songs(std::vector<Song*> songs);
private:
	User *user;
	std::vector<Criteria*> filters;
	void remove_filter(int index);
};
#endif