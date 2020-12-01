#ifndef VILLAGER_H
#define VILLAGER_H
#include "Player.hpp"
#include<iostream>

constexpr char VILLAGER_ROLE[] = "villager";

class Villager : public Player
{
public:
	Villager(std::string _name);
	virtual std::string get_role(){return VILLAGER_ROLE;}
};
#endif