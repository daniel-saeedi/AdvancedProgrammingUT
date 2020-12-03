#ifndef DETECTIVE_H
#define DETECTIVE_H
#include "Villager.hpp"
#include <iostream>

constexpr char DETECTIVE_ROLE[] = "detective";

class Detective : public Villager
{
public:
	Detective(std::string _name);
	virtual std::string get_role(){return DETECTIVE_ROLE;}
	virtual Player* vote_at_night(Player* votee);
	virtual void reset();
private:
	bool already_asked;
};
#endif