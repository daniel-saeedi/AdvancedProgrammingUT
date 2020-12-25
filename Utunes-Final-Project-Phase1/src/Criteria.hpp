#ifndef CRITERIA_H
#define CRITERIA_H
#include <iostream>
#include <vector>
#include "Song.hpp"
class Criteria
{
public:
	virtual std::vector<Song*> meet_criteria(std::vector<Song*> songs) = 0;
};
#endif