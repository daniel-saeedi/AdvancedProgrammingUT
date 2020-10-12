#include<iostream>
#include<cmath>
using namespace std;

//The recursive way to calculate the sum of digits

int sumOfDigits(int n) 
{ 
	//Base Case
    if (n == 0)
       return 0;

    //Recursive Case 
    return (n % 10 + sumOfDigits(n / 10)); 
} 

int main()
{
	cout << sumOfDigits(123456789);
	return 0;
}