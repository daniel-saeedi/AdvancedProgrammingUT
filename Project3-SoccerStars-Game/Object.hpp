#ifndef OBJECT_H
#define OBJECT_H
#include<iostream>

class Object
{
public:
	Object(int init_x,int init_y,int _radius,int _mass) : x(init_x), y(init_y), radius(_radius), mass(_mass), vx(0), vy(0){};
	void Reflect(std::string type);
	void Move(double dt);

	int GetRadius(){return radius;}
	double GetX(){return x;}
	double GetY(){return y;}
	int GetMass(){return mass;}
	double GetVx(){return vx;}
	double GetVy(){return vy;}
	void SetX(double _x){x = _x;}
	void SetY(double _y){y = _y;}
	void SetVx(double _vx){vx = _vx;}
	void SetVy(double _vy){vy = _vy;}
protected:
	int radius;
	double x;
	double y;
	double vx;
	double vy;
	int mass;
	int acceleration;
};

#endif