#include "Ball.hpp"

//Constructor
Ball::Ball(int _position_x,int _position_y)
{
	position_x = _position_x;
	position_y = _position_y;
	width = 40;
	height = 40;
	ball_image = "Assets/ball.png";
	vx = 0;
	vy = 0;
	mass = 1;
}

void Ball::Reflect(std::string type)
{
	if(type == "y") vy = -vy;
	else if(type == "x") vx = -vx;
	else if(type == "xy")
	{
		vx = -vx;
		vy = -vy;
	}
}