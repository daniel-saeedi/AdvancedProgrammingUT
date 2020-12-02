#ifndef GODFATHER_H
#define GODFATHER_H
#include "Mafia.hpp"

constexpr char GODFATHER_ROLE[] = "godfather";

class Godfather : public Mafia
{
public:
	Godfather(std::string _name);
	virtual std::string get_role(){return GODFATHER_ROLE;}
	virtual std::string are_you_mafia(){return "No";}
};
#endif