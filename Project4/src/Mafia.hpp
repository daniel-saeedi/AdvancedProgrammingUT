#ifndef MAFIA_H
#define MAFIA_H
#include "Player.hpp"
constexpr char MAFIA_ROLE[] = "mafia";
class Mafia : public Player
{
public:
	Mafia(std::string _name);
	virtual std::string get_role(){return MAFIA_ROLE;}
};
#endif