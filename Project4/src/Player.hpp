#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>

constexpr char PLAYER_ROLE[] = "player";

class Player
{
public:
	Player(std::string _name) : name(_name) {};

	std::string get_name(){return name;}

	virtual std::string get_role(){return PLAYER_ROLE;}
private:
	std::string name;
};
#endif