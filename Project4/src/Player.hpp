#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
class Player
{
public:
	Player(std::string _name) : name(_name) {};
private:
	std::string name;
};
#endif