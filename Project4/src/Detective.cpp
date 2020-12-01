#include "Detective.hpp"

Detective::Detective(std::string _name) : Villager(_name)
{
	wakeup_during_night = true;
}