#include <iostream>
#include <fstream>
using namespace std;

//I use flood fill algorithm for this function
bool searchAdjacent(vector<vector<int>> map,string word,vector<vector<char>> table[5][5],int x = 3,int y = 1, int index = 0)
{
	//Base Case
	if(x > (table.size()-1) || y > (table.size() - 1))
	{
		return false;
	}

	if(x < 0 || y < 0) return false;

	if((index) == word.size())return true;

	if(table[x][y] != word[index])
	{
		return false;
	}

	map[x][y] = index + 1;

	//We have to change the current letter for avoiding repetition in searching
	// - means we already went through this cell
	table[x][y] = '-'; 

	//Recursive Case
	bool found = searchAdjacent(map,word,table,x+1,y,index+1) 
		|| searchAdjacent(map,word,table,x-1,y,index+1) 
		|| searchAdjacent(map,word,table,x,y+1,index+1)
		|| searchAdjacent(map,word,table,x,y-1,index+1)
		|| searchAdjacent(map,word,table,x+1,y+1,index+1)
		|| searchAdjacent(map,word,table,x-1,y-1,index+1)
		|| searchAdjacent(map,word,table,x-1,y+1,index+1)
		|| searchAdjacent(map,word,table,x+1,y-1,index+1);

	//After We are done with searching in this cell, We change it back
	table[x][y] = word[index];
	return found;
	
}

//Finding the first letter of given word
void findTheFirstLetter()
{
	for(int i = 0 ;i < 5;i++)
	{
		for(int j = 0 ;j < 5;j++)
		{
			f >> table[i][j];
		}
	}
}

int main()
{
	ifstream f;
	f.open("P3/2.in");

	char table[5][5];

	for(int i = 0 ;i < 5;i++)
	{
		for(int j = 0 ;j < 5;j++)
		{
			f >> table[i][j];
		}
	}


	f.close();

	searchAdjacent("secret",table);

	for(int i = 0 ;i < 5;i++)
	{
		for(int j = 0 ;j < 5;j++)
		{
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}