#include "Doctor.hpp"
#include "Exception/AlreadyHealedException.hpp"
#include "Exception/PatientIsDeadException.hpp"

Doctor::Doctor(std::string _name) : Villager(_name)
{
	wakeup_during_night = true;
	already_healed = false;
}

Player* Doctor::vote_at_night(Player* votee)
{
	if(already_healed) throw AlreadyHealedException();
	if(!votee->get_is_alive()) throw PatientIsDeadException();
	already_healed = true;
	votee->set_is_healed(true);
	return nullptr;
}

void Doctor::reset()
{
	already_healed = false;
	is_healed = false;
}