#ifndef BALL_H
#define BALL_H

#include "Object.hpp"
#include <string>

class Ball : public Object
{
public:
	Ball(int init_x,int init_y,int _radius,int _mass);
	void CollideWithEdges(int width,int height);

	std::string get_ball_image(){return ball_image;}
private:
	std::string ball_image;
};


#endif