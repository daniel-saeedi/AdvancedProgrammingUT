#include "Physics.hpp"
#define COLLIDE_MOVE_TIME 0.017

bool Physics::CollisionDetector(Object *object1,Object *object2)
{
	if(object1 != object2)
	{
		double r1 = object1->GetRadius();
		double r2 = object2->GetRadius();
		Point distance;
		distance.x = object2->GetX() - object1->GetX();
		distance.y = object2->GetY() - object1->GetY();
		double d = VectorSize(distance);
		if(d < r1+r2) return true;
		else return false;
	}
	else return false;
}

bool Physics::Collision(Object *object1,Object *object2)
{
	bool collided = CollisionDetector(object1,object2);
	if(collided)
	{
		std::vector<Point> new_velocities = CalculateCollisionVelocity(object1,object2);
		object1->SetVx(new_velocities[0].x);
		object1->SetVy(new_velocities[0].y);
		object2->SetVx(new_velocities[1].x);
		object2->SetVy(new_velocities[1].y);
		object1->Move(COLLIDE_MOVE_TIME);
		object2->Move(COLLIDE_MOVE_TIME);
	}
	return collided;
}

std::vector<Point> Physics::CalculateCollisionVelocity(Object *object1,Object *object2)
{
	std::vector<Point> new_velocities;
	Point v1(object1->GetVx(),object1->GetVy());
	Point x1(object1->GetX(),object1->GetY());
	Point v2(object2->GetVx(),object2->GetVy());
	Point x2(object2->GetX(),object2->GetY());
	Point x1_x2 = SubtractVector(x1,x2);
	Point x2_x1 = VectorMultiplication(-1,x1_x2);
	Point v1_v2 = SubtractVector(v1,v2);
	Point v2_v1 = VectorMultiplication(-1,v1_v2);
	int mass1 = object1->GetMass();
	int mass2 = object2->GetMass();
	int coeff  =(2*mass2)/(mass1+mass2)*((DotProduct(v1_v2,x1_x2))/pow(VectorSize(x1_x2),2));
	int coeff2 =(2*mass1)/(mass1+mass2)*((DotProduct(v2_v1,x2_x1))/pow(VectorSize(x2_x1),2));
	new_velocities.push_back(SubtractVector(v1,VectorMultiplication(coeff,x1_x2)));
	new_velocities.push_back(SubtractVector(v2,VectorMultiplication(coeff2,x2_x1)));
	return new_velocities;
}

Point Physics::CalculateVelocity(Point d,int d_size)
{
	Point v;
	int denominator;
	if(d_size < throw_radius) denominator = throw_radius;
	else denominator = d_size;
	v.x = ((-1)*d.x*max_initial_speed)/denominator;
	v.y = ((-1)*d.y*max_initial_speed)/denominator;
	return v;
}
