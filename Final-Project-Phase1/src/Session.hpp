#ifndef SESSION_H
#define SESSION_H
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
constexpr int ARTIST_INDEX = 0;
constexpr int PUBLISH_YEAR_INDEX = 1;
constexpr int LIKE_INDEX = 2;
constexpr int FILTERS_SIZE = 3;
class Session
{
public:
	Session(User *_user);
	bool is_songs_filtered();
	void show_songs(std::vector<Song*> songs);
	User* get_user(){return user;}
	void add_artist_filter(std::string artist);
	void add_public_year_filter(int min,int max);
	void add_likes_filter(int min,int max);
	void delete_filters();
private:
	User *user;
	bool songs_filter_status;
	std::vector<Criteria*> filters;
	void remove_filter(int index);
};
#endif