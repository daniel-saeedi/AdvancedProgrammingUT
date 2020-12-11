#ifndef BULLETPROOF_H
#define BULLETPROOF_H
#include "Villager.hpp"

constexpr char BULLETPROOF_ROLE[] = "bulletproof";

class Bulletproof : public Villager
{
public:
	Bulletproof(std::string _name);
	virtual std::string get_role(){return BULLETPROOF_ROLE;}
	virtual void kill();
private:
	bool has_vest;
};
#endif