#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

//-1 means the key is not in numbers array
// We pass numbers vector by reference because we want to avoid copying numbers vector in every stack frame
int binarySearch(vector<int>& numbers,int from ,int to,int key)
{

	//Base Case
	if(numbers.size() == 0 || from > to) return -1;

	int mid = floor((from + to)/2);

	if(numbers[mid] == key) return mid;

	else if(numbers[mid] > key) return binarySearch(numbers,from,mid-1,key);
	else return binarySearch(numbers,mid+1,to,key);
}

int main()
{
	vector<int> numbers = {1,2,3,4,5,6};

	cout << binarySearch(numbers,0,numbers.size(),2);
	return 0;
}