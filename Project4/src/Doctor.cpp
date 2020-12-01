#include "Doctor.hpp"

Doctor::Doctor(std::string _name) : Villager(_name)
{
	wakeup_during_night = true;
}