#include "Object.hpp"
#include<cmath>

//Constructor
void Object::Reflect(std::string type)
{
	if(type == "y") vy = -vy;
	else if(type == "x") vx = -vx;
	else if(type == "xy")
	{
		vx = -vx;
		vy = -vy;
	}
}

void Object::Move(double dt)
{
	double v = sqrt(pow(vx,2)+pow(vy,2));
	if(v != 0)
	{
		double sin = (vy/v);
		double cos = (vx/v);
		v -= acceleration*dt;
		if(v <= 0)
		{
			vx = 0;
			vy=0;
		}
		else
		{
			if(vx != 0) vx = cos*v;
			if(vy != 0) vy = sin*v;
		}

		x += vx*dt;
		y += vy*dt;
	}
}
