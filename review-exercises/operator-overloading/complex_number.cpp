#include <iostream>
#include <fstream>
using namespace std;

class Complex
{
public:
	Complex(double _real,double _imag) : real(_real),imag(_imag){}
	Complex(double r) : real(r), imag(0) {}
	double re() const {return real;}
	double im() const {return imag;}
	Complex operator+(const Complex& c) const;
	Complex operator+(double n) const;
	bool operator==(const Complex& c) const;
	Complex& operator+=(const Complex& c);
	void print() const;
private:
	double real;
	double imag;
};

Complex Complex::operator+(const Complex& c) const
{
	double real2 = c.re();
	double imag2 = c.im();
	return Complex(real + real2,imag + imag2);
}
Complex Complex::operator+(double n) const
{
	return Complex(real + n,imag);
}

Complex operator+(double n,const Complex& c)
{
	return Complex(c.re() + n,c.im());
}

Complex& Complex::operator+=(const Complex& c)
{
    real += c.real;
    imag += c.imag;
    return *this;
}

ostream& operator<<(ostream& out,const Complex& c)
{
	out << c.re();
	double imag = c.im();
	if (imag > 0)
		out << '+' << imag << 'i';
	else if (imag < 0)
		out << imag << 'i';
	return out;
}

bool Complex::operator==(const Complex& c) const
{
	if(c.re() == real && c.im() == imag) return  true;
	return false;
}

void Complex::print() const
{
	cout << real;
	if (imag > 0)
		cout << '+' << imag << 'i';
	else if (imag < 0)
		cout << imag << 'i';
	cout << endl;
}

int main()
{
	Complex a(1,2);
	Complex b(0,3);
	Complex c = a+b;
	c = a+c;
	cout << c << endl;
	//c.print();
	c = c + 5;
	if(a == b)
		cout << c;
	return 0;
}