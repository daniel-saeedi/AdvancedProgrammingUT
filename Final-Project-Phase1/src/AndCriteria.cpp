#include "AndCriteria.hpp"
std::vector<Song*> AndCriteria::meet_criteria(std::vector<Song*> songs)
{
	std::vector<Song*> result = songs;
	for(int i = 0;i < filters.size();i++)
	{
		result = filters[i]->meet_criteria(result);
	}
	return result;
}