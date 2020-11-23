#ifndef PHYSICS_H
#define PHYSICS_H
#include <iostream>
#include <vector>
#include "functions.hpp"
#include "Object.hpp"
#include "rsdl.hpp"

class Physics
{
public:
	Physics(int _throw_radius,int _max_initial_speed,int _width,int _height) : throw_radius(_throw_radius), max_initial_speed(_max_initial_speed), width(_width), height(_height){};
protected:
	int throw_radius;
	int max_initial_speed;
	int width;
	int height;
	bool CollisionDetector(Object *object1,Object *object2);
	bool Collision(Object *object1,Object *object2);
	std::vector<Point> CalculateCollisionVelocity(Object *object1,Object *object2);
	Point CalculateVelocity(Point d,int d_size);
};

#endif