#ifndef DOCTOR_H
#define DOCTOR_H
#include "Villager.hpp"

constexpr char DOCTOR_ROLE[] = "doctor";

class Doctor : public Villager
{
public:
	Doctor(std::string _name);
	virtual std::string get_role(){return DOCTOR_ROLE;}
	virtual Player* vote_at_night(Player* votee);
	virtual void reset();
private:
	bool already_healed;
};
#endif