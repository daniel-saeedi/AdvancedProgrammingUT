#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

class Player
{
public:
	Player(int _position_x,int _position_y,int _team_id);

	// void set_position(int _position_x);
	// void set_position(int _position_x);

	int get_width(){return width;}
	int get_height(){return height;}
	int get_position_x(){return position_x;}
	int get_position_y(){return position_y;}
	std::string get_player_image(){return player_image;}
private:
	int width;
	int height;
	int position_x;
	int position_y;
	int team_id;
	int vx;
	int vy;
	std::string player_image;
};
#endif