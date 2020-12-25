#include "LikesCriteria.hpp"
LikesCriteria::LikesCriteria(int _min,int _max)
{
	if(_min > _max || _min < 0 || _max < 0) throw BadRequestException();
	min = _min;
	max = _max;
}
std::vector<Song*> LikesCriteria::meet_criteria(std::vector<Song*> songs)
{
	std::vector<Song*> result;
	for(int i = 0;i < songs.size();i++)
	{
		int likes = songs[i]->get_likes();
		if(likes >= min && likes <= max) result.push_back(songs[i]);
	}
	return result;
}