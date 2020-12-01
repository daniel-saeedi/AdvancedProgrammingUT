#include "Mafia.hpp"

Mafia::Mafia(std::string _name) : Player(_name)
{
	wakeup_during_night = true;
}