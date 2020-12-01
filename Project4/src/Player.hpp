#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>

constexpr char PLAYER_ROLE[] = "player";

class Player
{
public:
	Player(std::string _name) : name(_name),is_silenced(false),is_alive(true){};

	std::string get_name(){return name;}
	virtual std::string get_role(){return PLAYER_ROLE;}
	void set_is_silenced(bool status){is_silenced = status;}
	void kill(){is_alive = false;}
	bool get_is_silenced(){return is_silenced;}
	bool get_is_alive(){return is_alive;}
protected:
	std::string name;
	bool is_silenced;
	bool is_alive;
};
#endif