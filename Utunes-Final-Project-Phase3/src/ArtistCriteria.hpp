#ifndef ARTIST_CRITERIA_H
#define ARTIST_CRITERIA_H
#include <iostream>
#include <vector>
#include "Song.hpp"
#include "Criteria.hpp"
class ArtistCriteria : public Criteria
{
public:
	ArtistCriteria(std::string _artist) : artist(_artist){};
	virtual std::vector<Song*> meet_criteria(std::vector<Song*> songs);
private:
	std::string artist;
};
#endif