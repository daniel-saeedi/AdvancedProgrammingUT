#ifndef DETECTIVE_H
#define DETECTIVE_H
#include "Villager.hpp"

constexpr char DETECTIVE_ROLE[] = "detective";

class Detective : public Villager
{
public:
	Detective(std::string _name);
	virtual std::string get_role(){return DETECTIVE_ROLE;}
};
#endif