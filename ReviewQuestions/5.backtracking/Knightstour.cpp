#include<iostream>
#include<vector>
using namespace std;

const int ROW_COUNT = 5;
const int COL_COUNT = 5;
const int POSSIBLE_MOVES = 8;

int row_delta[POSSIBLE_MOVES] = {2, 1, -1, -2, -2, -1, 1, 2};
int col_delta[POSSIBLE_MOVES] = {-1, -2, -2, -1, 1, 2, 2, 1};

bool boundaryCheck(int row,int col)
{
	if(row >= ROW_COUNT || col >= COL_COUNT || row < 0 || col < 0) return false;

	return true;
}


bool find_tour(int board[ROW_COUNT][COL_COUNT],int current_row,int current_column,int moves = 1)
{
	//Base Case
	if(!boundaryCheck(current_row,current_column)) return false;

	if(moves == ROW_COUNT*COL_COUNT) return true;

	//Recursive Case

	for(int i = 0;i < POSSIBLE_MOVES;i++)
	{
		int new_row = current_row + row_delta[i];
		int new_col = current_column + col_delta[i];

		if(!boundaryCheck(new_row,new_col)) continue;

		if(board[new_row][new_col] != 0) continue;

		board[new_row][new_col] = moves + 1;

		if(find_tour(board,new_row,new_col,moves+1)) return true;

		board[new_row][new_col] = 0;
	}

	return false;
}


void solve(int board[ROW_COUNT][COL_COUNT],int row_start,int col_start)
{
	board[row_start][col_start] = 1;
	bool possible = find_tour(board,row_start,col_start);

	cout << possible << endl;
}


int main()
{
	int board[ROW_COUNT][COL_COUNT] = {0};

	solve(board,2,2);

	for(int i = 0;i<ROW_COUNT;i++)
	{
		for(int j = 0;j < COL_COUNT;j++)
		{
			cout << board[i][j] << "\t";
		}

		cout << endl;
	}
	return 0;
}















