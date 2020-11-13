#include "Stadium.hpp"
#include "Player.hpp"
#include "Ball.hpp"
#include<string>

//Constructor
Stadium::Stadium(int _width,int _height)
{
	width = _width;
	height = _height;
}

void Stadium::CollideWithEdges(Player *player)
{
	int radius = player->get_width()/2;
	int center_x = player->get_center_x();
	int center_y = player->get_center_y();
	int top_corner = center_y - radius;
	int bottom_corner = center_y + radius;
	int left_corner = center_x - radius;
	int right_corner = center_x + radius;

	if(top_corner <= 0) player->Reflect("y");
	else if(bottom_corner >= height) player->Reflect("y");
	else if(left_corner <= 0) player->Reflect("x");
	else if(right_corner >= width) player->Reflect("x");
}