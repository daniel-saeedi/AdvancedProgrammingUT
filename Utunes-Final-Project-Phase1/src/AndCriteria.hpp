#ifndef AND_CRITERIA_H
#define AND_CRITERIA_H
#include <iostream>
#include <vector>
#include "Song.hpp"
#include "Criteria.hpp"
class AndCriteria : public Criteria
{
public:
	AndCriteria(std::vector<Criteria*> _filters) : filters(_filters) {};
	virtual std::vector<Song*> meet_criteria(std::vector<Song*> songs);
private:
	std::vector<Criteria*> filters;
};
#endif