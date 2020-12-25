#ifndef PUBLISH_YEAR_CRITERIA_H
#define PUBLISH_YEAR_CRITERIA_H
#include <iostream>
#include <vector>
#include "Song.hpp"
#include "Criteria.hpp"
#include "Exception/BadRequestException.hpp"
class PublishYearCriteria : public Criteria
{
public:
	PublishYearCriteria(int _min_year,int _max_year);
	virtual std::vector<Song*> meet_criteria(std::vector<Song*> songs);
private:
	int min_year;
	int max_year;
};
#endif