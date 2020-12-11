#include "Bulletproof.hpp"

Bulletproof::Bulletproof(std::string _name) : Villager(_name)
{
	has_vest = true;
}

void Bulletproof::kill()
{
	if(!is_healed)
	{
		if(!has_vest) is_alive = false;
		else has_vest = false;
	}
	else is_healed = false;
}