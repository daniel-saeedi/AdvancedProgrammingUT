#ifndef PLAYER_H
#define PLAYER_H

#include "Object.hpp"
#include <iostream>
#include <string>

class Player : public Object
{
public:
	Player(int init_x,int init_y,int _radius,int _mass,int _team_id);
	void CollideWithEdges(int width,int height);

	std::string get_player_image(){return player_image;}
private:
	int team_id;
	std::string player_image;
};
#endif