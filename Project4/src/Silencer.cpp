#include "Silencer.hpp"
#include "Exception/PersonIsDeadException.hpp"

Silencer::Silencer(std::string _name) : Mafia(_name)
{
	has_silenced = false;
}

Player* Silencer::vote_at_night(Player* votee)
{
	if(has_silenced) return votee;
	else
	{
		if(!votee->get_is_alive()) throw PersonIsDeadException();
		has_silenced = true;
		votee->silence(true);
		return nullptr;
	}
}

void Silencer::reset()
{
	has_silenced = false;
	is_healed = false;
}