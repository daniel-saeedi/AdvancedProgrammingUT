/*
* Daniel Saeedi
* Advanced Programming Project 1
* fucking 2020
*/
#include<iostream>
#include<vector>
#include <sstream>
#include <string>
#include<fstream>
using namespace std;

struct Movie
{
	string CinemaName;
	string MovieName;
	string Day;
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
			case 3: newMovie->Day = substr;
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
	int lineNumber = 1;
	string line;
	ifstream file("schedule.csv");

	while (getline(file, line))
	{
		if(lineNumber > 1)
		{
			movies.push_back(readMovieInfo(line));
		}
		lineNumber++;
	}

	file.close();
}

// void sortByName(vector<Movie*>& movies)  
// {  
//     int i, j;
// 	for (i = 0; i < movies.size()-1; i++)
// 	{ 
// 		for (j = 0; j < movies.size()-i-1; j++)
// 		{
// 			if (movies[j]->MovieName > movies[j+1]->MovieName)
// 			{
// 				Movie *temp;

// 				temp = movies[j+1];
// 				movies[j+1] = movies[j];
// 				movies[j] = temp;
// 			}
// 		}
// 	}
// }

void sortByName(vector<Movie*>& movies)  
{
   int i, j; 
   bool swapped; 
   for (i = 0; i < movies.size()-1; i++) 
   { 
     swapped = false; 
     for (j = 0; j < movies.size()-i-1; j++) 
     { 
        if (movies[j]->MovieName > movies[j+1]->MovieName)
        { 
			Movie *temp;

			temp = movies[j+1];
			movies[j+1] = movies[j];
			movies[j] = temp;
			swapped = true; 
        } 
     } 
  
     // IF no two elements were swapped by inner loop, then break 
     if (swapped == false) 
        break; 
   } 
}

bool compare_by_word(Movie* lhs,Movie* rhs) {
    return lhs->MovieName < rhs->MovieName;
}
  
void showAllMovies(vector<Movie*>& movies)
{
	//sortByName(movies);
	sort(movies.begin(), movies.end(), compare_by_word);
	string currentMovie = "";
	for(int i = 0;i < movies.size();i++)
	{
		
		if(currentMovie != movies[i]->MovieName)
		{
			cout << movies[i]->MovieName << endl;

			currentMovie = movies[i]->MovieName;
		}
	}
}

int main()
{
	int userCommand = 0;

	vector<Movie*> movies;

	readSchedule(movies);

	cout << "If you want to get the list of movies enter : 1" << endl;
	cin >> userCommand;
	switch(userCommand)
	{
		case 1: showAllMovies(movies);
		case 2: showAllMovies(movies);
		default: cout << "Wrong Command";
	}
	return 0;
}













