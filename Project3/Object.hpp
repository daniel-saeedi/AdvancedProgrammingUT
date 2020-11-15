#ifndef OBJECT_H
#define OBJECT_H
#include<iostream>

class Object
{
public:
	Object(int init_x,int init_y,int _radius,int _mass) : x(init_x), y(init_y), radius(_radius), mass(_mass), vx(0), vy(0){};
	void Reflect(std::string type);
	void Move(double dt);

	int get_radius(){return radius;}
	int get_x(){return x;}
	int get_y(){return y;}
	int get_mass(){return mass;}
	double get_vx(){return vx;}
	double get_vy(){return vy;}
	void set_x(int _x){x = _x;}
	void set_y(int _y){y = _y;}
	void set_vx(double _vx){vx = _vx;}
	void set_vy(double _vy){vy = _vy;}
protected:
	int radius;
	int x;
	int y;
	double vx;
	double vy;
	int mass;
	int acceleration;
};

#endif