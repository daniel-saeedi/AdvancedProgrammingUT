#include "Detective.hpp"
#include "Exception/SuspectIsDeadException.hpp"
#include "Exception/AlreadyAskedException.hpp"

Detective::Detective(std::string _name) : Villager(_name)
{
	wakeup_during_night = true;
	already_asked = false;
}

Player* Detective::vote_at_night(Player* votee)
{
	if(already_asked) throw AlreadyAskedException();
	if(!votee->get_is_alive()) throw SuspectIsDeadException();
	std::cout << votee->is_mafia() << std::endl;
	already_asked = true;
	return nullptr;
}