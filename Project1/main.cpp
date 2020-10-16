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

void extractTime(string time,int &hour,int &minute)
{
	stringstream ss(time);
	int index = 1;
	while( ss.good() )
	{
		string substr;
		getline( ss, substr,':');

		if(index == 1) hour = stoi(substr);
		if(index == 2) minute = stoi(substr);

		index++;
	}
}

bool compareByWord(Movie* lhs,Movie* rhs) {
    return lhs->MovieName < rhs->MovieName;
}

bool compareByTime(Movie* lhs,Movie* rhs) {
	int hourMovie1,minuteMovie1 = 0;
	int hourMovie2,minuteMovie2 = 0;
	extractTime(lhs->StartingTime,hourMovie1,minuteMovie1);
	extractTime(rhs->StartingTime,hourMovie2,minuteMovie2);
	return hourMovie1*60 + minuteMovie1 < hourMovie2*60 + minuteMovie2;
}

bool compareByNumber(Movie* lhs,Movie* rhs) {
    return lhs->Price < rhs->Price;
}

bool compareByTimeString(string time1,string time2) {
	int hour1,minute1 = 0;
	int hour2,minute2 = 0;
	extractTime(time1,hour1,minute1);
	extractTime(time2,hour2,minute2);
	return hour1*60 + minute1 > hour2*60 + minute2;
}
  
void printAllMovies(vector<Movie*>& movies)
{
	sort(movies.begin(), movies.end(), compareByWord);
	string currentMovie = "";

	for(int i = 0;i < movies.size();i++)
	{
		cout << movies[i]->MovieName << endl;
		if(currentMovie != movies[i]->MovieName)
		{
			
			currentMovie = movies[i]->MovieName;
		}
	}
}

//This function finds start and end of movie x in movies vector(sorted by alphabetical order)
void findStartAndEnd(vector<Movie*>& movies,int &start,int &end,string movieName)
{
	bool find = false;
	for(int i = 0;i < movies.size();i++)
	{
		if(movies[i]->MovieName == movieName && find == false)
		{
			start = i;
			find = true;
		}

		else if(movies[i]->MovieName != movieName && find == true)
		{
			end = i-1;
			find = false;
		}

		else if(find == true && i == movies.size() - 1 && movies[i]->MovieName == movieName)
		{
			end = i;
			find = false;
		}
	}
}

void findOverlappingTime(vector<vector<Movie*> > &plan,int day,vector<vector<Movie*> > &selected)
{
	int start = 0,end = 0;
	string finishingTime;
	for(int i =0;i < plan[day].size();)
	{
		finishingTime = plan[day][i]->FinishingTime;
		//start = i;
		end = i;

		vector<Movie*> selectedMovie;
		selectedMovie.push_back(plan[day][i]);
		for(int j = i+1;j < plan[day].size();j++)
		{
			if(compareByTimeString(finishingTime,plan[day][j]->StartingTime))
			{
				end = j;
			}

			if(plan[day][i]->StartingTime == plan[day][j]->StartingTime) selectedMovie.push_back(plan[day][j]);
		}

		if(selectedMovie.size() == 1)
		{
			selected[day].push_back(selectedMovie[0]);
		}
		else
		{
			
			sort(selectedMovie.begin(), selectedMovie.end(), compareByNumber);
			vector<Movie*> selectedMovie2;
			selectedMovie2.push_back(selectedMovie[0]);
			for(int j = 1;j < selectedMovie.size();j++)
			{
				if(selectedMovie[0]->Price == selectedMovie[j]->Price) selectedMovie2.push_back(selectedMovie[j]);
			}

			if(selectedMovie2.size() == 0)
			{
				selected[day].push_back(selectedMovie[0]);
			}

			else
			{
				sort(selectedMovie2.begin(), selectedMovie2.end(), compareByWord);

				selected[day].push_back(selectedMovie2[0]);
			}
		}

		i = end + 1;
	}
}

void constructPlan(vector<vector<Movie*> > &plan,vector<Movie*>& movies,string movieName,vector<vector<Movie*> > &selected)
{
	vector<Movie*> movie;
	/*
	Initializing plan vector
	Row 0: Saturday,1 : Sunday .... 6:Friday*/
	for(int i = 0;i < 7;i++)
	{
		plan.push_back(movie);
	}

	/*
	Initializing selected vector
	Row 0: Saturday,1 : Sunday .... 6:Friday*/
	for(int i = 0;i < 7;i++)
	{
		selected.push_back(movie);
	}

	//First We sort movies vector by Movie Name
	sort(movies.begin(), movies.end(), compareByWord);

	//Then we find where movie x starts and ends in movies vector(sorted by alphabetical order)
	int start,end = 0;
	findStartAndEnd(movies,start,end,movieName);

	for(int i = start; i <= end;i++)
	{
		if(movies[i]->Day == "Saturday") plan[0].push_back(movies[i]);
		else if(movies[i]->Day == "Sunday") plan[1].push_back(movies[i]);
		else if(movies[i]->Day == "Monday") plan[2].push_back(movies[i]);
		else if(movies[i]->Day == "Tuesday") plan[3].push_back(movies[i]);
		else if(movies[i]->Day == "Wednesday") plan[4].push_back(movies[i]);
		else if(movies[i]->Day == "Thursday") plan[5].push_back(movies[i]);
		else if(movies[i]->Day == "Friday") plan[6].push_back(movies[i]);
	}

	//Sorting Plan vector by starting and finishing time
	for(int i = 0; i < 7;i++)
	{
		sort(plan[i].begin(), plan[i].end(), compareByTime);
		findOverlappingTime(plan,i,selected);
	}


	// cout << endl << endl << endl;

	// for(int i = 0;i < plan.size();i++)
	// {
	// 	cout << "Day : " <<i + 1 << endl;
	// 	for(int j = 0;j < plan[i].size();j++)
	// 	{
	// 		cout << plan[i][j]->StartingTime << " to " << plan[i][j]->FinishingTime << " Price : " << plan[i][j]->Price << " Cinema :" << plan[i][j]->CinemaName << endl;
	// 	}
	// 	cout << endl;
	// }
	cout << endl << endl << endl;
	for(int i = 0;i < selected.size();i++)
	{
		cout << "Day : " <<i + 1 << endl;
		for(int j = 0;j < selected[i].size();j++)
		{
			cout << selected[i][j]->StartingTime << " to " << selected[i][j]->FinishingTime << " Price : " << selected[i][j]->Price << " Cinema :" << selected[i][j]->CinemaName << endl;
		}
		cout << endl;
	}
}

void constructHTML(vector<vector<Movie*> > selected)
{
	ofstream web("web.html");
	ifstream ifs("header.html");

	string header((istreambuf_iterator<char>(ifs)),(istreambuf_iterator<char>()));

	web << header;
	int width = 0,left = 0,top = 0;

	int startH = 0,startM = 0;
	int finishH = 0,finishM = 0;
	for(int i = 0; i < selected.size();i++)
	{
		for(int j = 0; j < selected[i].size();j++)
		{
			

			extractTime(selected[i][j]->StartingTime,startH,startM);
			extractTime(selected[i][j]->FinishingTime,finishH,finishM);

			int diffTime = (finishH*60+ finishM)-(startH*60+ startM);
			width = 50 * (diffTime/30);
			left = 100 + 50 * (((startH-8)*60+ startM)/30);
			top = 60 + i*50;
			web << "<div class='record-box' style='" << "width: "<< width <<"px; left: "<< left<<"; top:"<< top <<"; '>"<< selected[i][j]->CinemaName<<"</div>";
		}
	}
	web << "</body></html>";

	ifs.close();
	web.close();
}

int main()
{
	string userCommand;

	vector<Movie*> movies;

	readSchedule(movies);

	cout << "If you want to get the list of movies enter : GET ALL MOVIES" << endl;
	getline(cin,userCommand);
	if(userCommand == "GET ALL MOVIES")
	{
		printAllMovies(movies);
	}
	else
	{
		string movieName = userCommand;

		vector<vector<Movie*> > plan;
		vector<vector<Movie*> > selected;

		constructPlan(plan,movies,movieName,selected);

		constructHTML(selected);
	}

	return 0;
}













