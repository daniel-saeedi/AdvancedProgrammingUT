#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

class Player
{
public:
	Player(int _position_x,int _position_y,int _team_id);
	void MovePlayer(double dt);
	void Reflect(std::string type);

	int get_width(){return width;}
	int get_height(){return height;}
	int get_position_x(){return position_x;}
	int get_position_y(){return position_y;}
	int get_center_x(){return position_x+width/2;}
	int get_center_y(){return position_y+height/2;}
	double get_vx(){return vx;}
	double get_vy(){return vy;}
	std::string get_player_image(){return player_image;}
	void set_position_x(int x){position_x = x;}
	void set_position_y(int y){position_y = y;}
	void set_vx(double _vx){vx = _vx;}
	void set_vy(double _vy){vy = _vy;}
	void set_tangent(double _tangent){tangent = _tangent;}
private:
	int width;
	int height;
	int position_x;
	int position_y;
	int team_id;
	double vx;
	double vy;
	int mass;
	int acceleration;
	double tangent;
	std::string player_image;
};
#endif