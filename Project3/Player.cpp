#include "Player.hpp"
#include<cmath>
#define TEAM_A 1
#define TEAM_B 2

//Constructor
Player::Player(int _position_x,int _position_y,int _team_id)
{
	if(_team_id == TEAM_A) player_image = "Assets/Player1.png";
	if(_team_id == TEAM_B) player_image = "Assets/Player2.png";
	position_x = _position_x;
	position_y = _position_y;
	team_id = _team_id;
	width = 70;
	height = 70;
	vx = 0;
	vy = 0;
	tangent = 0;
	mass = 2;
	acceleration = 10;
}

void Player::MovePlayer(double dt)
{
	double v = sqrt(pow(vx,2)+pow(vy,2));
	if(v != 0)
	{
		double sin = abs(vy/v);
		double cos = abs(vx/v);

		v -= acceleration;
		if(v < 0) 
		{
			vx = 0;
			vy=0;
		}
		else
		{
			vx = cos*v*(vx/abs(vx));
			vy = sin*v*(vy/abs(vy));
		}

		position_x += vx*dt;
		position_y += vy*dt;
	}
}

void Player::Reflect(std::string type)
{
	if(type == "y") vy = -vy;
	else if(type == "x") vx = -vx;
	else if(type == "xy")
	{
		vx = -vx;
		vy = -vy;
	}
}