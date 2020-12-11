#ifndef MAFIA_H
#define MAFIA_H
#include "Player.hpp"
#include "VoteSystem.hpp"
constexpr char MAFIA_ROLE[] = "mafia";
class Mafia : public Player
{
public:
	Mafia(std::string _name);
	virtual std::string get_role(){return MAFIA_ROLE;}
	virtual Player* vote_at_night(Player* votee);
	virtual std::string are_you_mafia(){return "Yes";}
	virtual bool is_mafia(){return true;}
	virtual void reset(){is_healed = false;}
};
#endif