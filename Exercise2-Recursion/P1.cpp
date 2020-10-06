#include <iostream>
using namespace std;

void encrypt(string text)
{
	int len = text.length();

	//Base case
	if(len == 0)
	{
		return;
	}

	int k = 0;
	if(len % 2 == 0)
	{
		k = (len/2)-1;
	}

	else
	{
		k  = ((len+2)/2)-1;
	}

	cout << text[k];

	//Recursive Case

	encrypt(text.substr(0,k));
	encrypt(text.substr(k+1,len-(k+1)));
}

int main()
{
	string word;
	cin >> word;

	encrypt(word);

	cout << endl;
	return 0;
}