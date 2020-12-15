#include "ArtistCriteria.hpp"

std::vector<Song*> ArtistCriteria::meet_criteria(std::vector<Song*> songs)
{
	std::vector<Song*> result;
	for(int i = 0;i < songs.size();i++)
	{
		if(songs[i]->is_artist_equal(artist)) result.push_back(songs[i]);
	}
	return result;
}