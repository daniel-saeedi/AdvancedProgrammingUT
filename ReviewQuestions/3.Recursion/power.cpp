#include <iostream>
using namespace std;

int power(int x,int n)
{
	//Base Case
	if(n <= 0) return 1;

	return x*power(x,n-1);
}

int main()
{
	cout << power(3,5);
	return 0;
}