#include "functions.hpp"
#include <cmath>

Point VectorMultiplication(int a,Point vector)
{
	Point result;
	result.x = vector.x*a;
	result.y = vector.y*a;
	return result;
}

int DotProduct(Point vector1,Point vector2)
{
	return vector1.x*vector2.x + vector1.y*vector2.y;
}

Point SubtractVector(Point vector1,Point vector2)
{
	Point subtract;
	subtract.x = vector1.x - vector2.x;
	subtract.y = vector1.y - vector2.y;
	return subtract;
}

int VectorSize(Point vector)
{
	return sqrt(pow(vector.x,2)+pow(vector.y,2));
}