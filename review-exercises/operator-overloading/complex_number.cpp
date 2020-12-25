#include <iostream>
using namespace std;

class Complex
{
public:
	Complex(double _real,double _imag) : real(_real),imag(_imag){};
	double re(){return real;}
	double im(){return imag;}
	void operator+()
	{

	}
private:
	double real;
	double imag;
}


int main()
{
	Complex a(1,2);
	Complex b(0,3);
	a = a+b;
	return 0;
}