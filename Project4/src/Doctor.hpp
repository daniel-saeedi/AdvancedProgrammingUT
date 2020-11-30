#ifndef DOCTOR_H
#define DOCTOR_H
#include "Villager.hpp"

constexpr char DOCTOR_ROLE[] = "doctor";

class Doctor : public Villager
{
public:
	Doctor(std::string _name);

	virtual std::string get_role(){return DOCTOR_ROLE;}
};
#endif