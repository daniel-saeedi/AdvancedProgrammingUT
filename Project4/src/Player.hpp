#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>

constexpr char PLAYER_ROLE[] = "player";

class Player
{
public:
	Player(std::string _name) : name(_name),is_silenced(false),is_alive(true),wakeup_during_night(false),is_healed(false){};

	std::string get_name(){return name;}
	virtual std::string get_role(){return PLAYER_ROLE;}
	void kill(){is_alive = false;}
	void silence(bool status){is_silenced = status;}
	bool get_is_silenced(){return is_silenced;}
	bool get_is_alive(){return is_alive;}
	bool can_wakeup(){return wakeup_during_night;}
	bool get_is_healed(){return is_healed;}
	void set_is_healed(bool status){is_healed = status;}
	virtual Player* vote_at_night(Player* votee){return nullptr;};
	virtual std::string is_mafia(){return "No";}
protected:
	std::string name;
	bool is_silenced;
	bool is_alive;
	bool wakeup_during_night;
	bool is_healed;
};
#endif