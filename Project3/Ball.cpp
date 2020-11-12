#include "Ball.hpp"

//Constructor
Ball::Ball(int _position_x,int _position_y)
{
	position_x = _position_x;
	position_y = _position_y;
	width = 50;
	height = 50;
	ball_image = "Assets/ball.png";
}