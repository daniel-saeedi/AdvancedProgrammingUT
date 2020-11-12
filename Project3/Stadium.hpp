#ifndef STADIUM_H
#define STADIUM_H

#include "Player.hpp"
#include "Ball.hpp"

class Stadium
{
public:
	Stadium(int width,int height);

	int get_width(){return width;}
	int get_height(){return height;}
private:
	int width;
	int height;
};

#endif