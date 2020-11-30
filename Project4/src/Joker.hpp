#ifndef JOKER_H
#define JOKER_H
#include "Player.hpp"

constexpr char JOKER_ROLE[] = "joker";

class Joker : public Player
{
public:
	Joker(std::string _name);

	virtual std::string get_role(){return JOKER_ROLE;}
};
#endif