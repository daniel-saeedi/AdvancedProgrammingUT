#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*I use flood fill idea for checking adjacent cells
*/
bool searchAdjacent(vector< vector<int> > &map,string word,vector< vector<char> > &table,int x = 3,int y = 1, int index = 0)
{
	//Base Case

	//checking if x and y are invalid
	if(x > (table.size()-1) || y > (table.size() - 1) || x < 0 || y < 0)
	{
		return false;
	}

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

int main()
{
	string word;
	cin >> word;
	
	int dim;
	cin >> dim;

	vector< vector<int> > map( dim , vector<int> (dim, 0)); 

	vector< vector<char> > table( dim , vector<char> (dim, 0));  


	for(int i = 0 ;i < dim;i++)
	{
		for(int j = 0 ;j < dim;j++)
		{
			cin >> table[i][j];
		}
	}

	//First I find the first letter of the given word and then search around that
	bool found = false;
	for(int i = 0 ;i < table.size();i++)
	{
		for(int j = 0 ;j < table.size();j++)
		{

			//Reseting Map
			for(int k = 0 ;k < table.size();k++)
			{
				for(int l = 0 ;l < table.size();l++)
				{
					map[k][l] = 0;
				}
			}

			if(table[i][j] == word[0])
			{
				if(searchAdjacent(map,word,table,i,j))
				{
					found = true;
					break;
				}
			}
		}
	}

	//Saving the results

	if(found)
	{
		cout << "Yes" << endl;

		for(int i = 0 ;i < map.size();i++)
		{
			for(int j = 0 ;j < map.size();j++)
			{
				cout << map[i][j];

				if(j != map.size()-1) cout << " ";
			}
			cout << endl;
		}
	}
	else cout << "No" << endl;
	return 0;
}