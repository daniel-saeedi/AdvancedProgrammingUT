#include "Ball.hpp"

//Constructor
Ball::Ball(int init_x,int init_y,int _radius,int _mass): Object(init_x,init_y,_radius,_mass)
{
	ball_image = "Assets/ball.png";
	acceleration = 500;
}

void Ball::CollideWithEdges(int width,int height)
{
	int top_corner = y - radius;
	int bottom_corner = y + radius;
	int left_corner = x - radius;
	int right_corner = x + radius;
	if(top_corner <= 0) {Reflect("y"); y = radius;}
	else if(bottom_corner >= height) {Reflect("y"); y = height - radius;}
	else if(left_corner <= 0) {Reflect("x"); x = radius;}
	else if(right_corner >= width) {Reflect("x"); x = width - radius;}
}