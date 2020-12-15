#include "PublishYearCriteria.hpp"
PublishYearCriteria::PublishYearCriteria(int _min_year,int _max_year)
{
	if(_min_year > _max_year || _min_year < 0 || _max_year < 0) throw BadRequestException();
	min_year = _min_year;
	max_year = _max_year;
}

std::vector<Song*> PublishYearCriteria::meet_criteria(std::vector<Song*> songs)
{
	std::vector<Song*> result;
	for(int i = 0;i < songs.size();i++)
	{
		int release_year = songs[i]->get_year();
		if(release_year >= min_year && release_year <= max_year) result.push_back(songs[i]);
	}
	return result;
}