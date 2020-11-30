#ifndef SILENCER_H
#define SILENCER_H
#include "Mafia.hpp"
#include<iostream>

constexpr char SILENCER_ROLE[] = "silencer";

class Silencer : public Mafia
{
public:
	Silencer(std::string _name);
	virtual std::string get_role(){return SILENCER_ROLE;}
};
#endif