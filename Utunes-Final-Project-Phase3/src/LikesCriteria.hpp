#ifndef LIKE_CRITERIA_H
#define LIKE_CRITERIA_H
#include <iostream>
#include <vector>
#include "Song.hpp"
#include "Criteria.hpp"
#include "Exception/BadRequestException.hpp"
class LikesCriteria : public Criteria
{
public:
	LikesCriteria(int _min,int _max);
	virtual std::vector<Song*> meet_criteria(std::vector<Song*> songs);
private:
	int min;
	int max;
};
#endif