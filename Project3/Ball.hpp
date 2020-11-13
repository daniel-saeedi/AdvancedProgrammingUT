
#ifndef BALL_H
#define BALL_H

#include <string>

class Ball
{
public:
	Ball(int _position_x,int _position_y);

	void Reflect(std::string type);

	std::string get_ball_image(){return ball_image;}
	int get_width(){return width;}
	int get_height(){return height;}
	int get_position_x(){return position_x;}
	int get_position_y(){return position_y;}
	int get_center_x(){return position_x+width/2;}
	int get_center_y(){return position_y+height/2;}

	void set_position_x(int x){position_x = x;}
	void set_position_y(int y){position_y = y;}
private:
	int width;
	int height;
	int position_x;
	int position_y;
	int vx;
	int vy;
	int mass;
	std::string ball_image;
};


#endif