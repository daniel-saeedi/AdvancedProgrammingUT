
#ifndef BALL_H
#define BALL_H

#include <string>

class Ball
{
public:
	Ball(int _position_x,int _position_y);

	std::string get_ball_image(){return ball_image;}
	int get_width(){return width;}
	int get_height(){return height;}
	int get_position_x(){return position_x;}
	int get_position_y(){return position_y;}
	void set_position_x(int x){position_x = x;}
	void set_position_y(int y){position_y = y;}
private:
	int width;
	int height;
	int position_x;
	int position_y;
	int vx;
	int vy;
	std::string ball_image;
};


#endif