#include<iostream>
#include<cmath>
using namespace std;

/*
* Review Question: Write a program that convert decimal numbers to binary numbers by recursion
*/

void convertToBinary(int number)
{
	//Base Case
	if(number < 0 || floor(number/2) == 1 || floor(number/2) == 0) 
	{
		cout << floor(number/2);
		cout << number%2;
		
		return;
	}

	convertToBinary(floor(number/2));

	cout << number%2;
}

int main()
{

	convertToBinary(500);
	return 0;
}


