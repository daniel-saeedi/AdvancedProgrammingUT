#ifndef JOKER_H
#define JOKER_H
#include "Player.hpp"

constexpr char JOKER_ROLE[] = "joker";

class Joker : public Player
{
public:
	Joker(std::string _name);
	virtual std::string get_role(){return JOKER_ROLE;}
	virtual bool is_joker(){return true;}
	virtual void reset(){is_healed = false;}
	virtual std::string are_you_mafia(){return "No";}
};
#endif