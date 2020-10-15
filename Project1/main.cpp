/*
* Daniel Saeedi
* Advanced Programming Project 3
* fucking 2020
*/
#include<iostream>
#include<vector>
#include <sstream>
#include <string>
using namespace std;

struct Movie
{
	string CinemaName;
	string MovieName;
	string Days;
	string StartingTime;
	string FinishingTime;
	string Price;
	string Hall;
};

Movie* readMovieInfo(string info)
{
	Movie *newMovie = new Movie;
	stringstream ss(info);

	Movie *next;

	int index = 1;
	while( ss.good() )
	{
		string substr;
		getline( ss, substr,',');
		switch(index)
		{
			case 1: newMovie->CinemaName = substr;
			case 2: newMovie->MovieName = substr;
			case 3: newMovie->Days = substr;
			case 4: newMovie->StartingTime = substr;
			case 5: newMovie->FinishingTime = substr;
			case 6: newMovie->Price = substr;
			case 7: newMovie->Hall = substr;
		}
		index++;
	}
	
	return newMovie;
}

void readSchedule(vector<Movie*>& movies)
{
	string line;

	int lineNumber = 1;

	while (getline(cin, line))
	{
		if(lineNumber > 1)
		{
			movies.push_back(readMovieInfo(line));
		}
		lineNumber++;
	}
}


int main()
{
	vector<Movie*> movies;

	readSchedule(movies);

	cout << movies[5]->MovieName;
	return 0;
}













