#include<iostream>
#include<vector>
#include <sstream>
#include <string>
using namespace std;

void splitBySpace(vector<string> &data,string text)
{
	stringstream ss(text);
	while( ss.good() )
	{
		string substr;
		getline( ss, substr,' ');
		data.push_back(substr);
	}
}

class Worker
{
public:
	//Constructor
	Worker(int time_coeff)
	{
		time_coefficient = time_coeff;
	}

	int get_time_coefficient() {return time_coefficient;}
private:
	int time_coefficient;
};

class Stage
{
public:
	void addWorker(Worker newWorker)
	{
		workers.push_back(newWorker);
	}

	void showWorkers()
	{
		for(int i = 0;i < workers.size();i++)
		{
			cout << workers[i].get_time_coefficient() << " ";
		}
	}
private:
	vector<Worker> workers;
};

class Car
{
public:
	Car(int luxury_coeff)
	{
		luxury_coefficient = luxury_coeff;
	}
private:
	int luxury_coefficient;
};



class CarWash
{
public:

	//Constructor
	CarWash();


private:
	vector<Stage> stages;
	vector<Car> cars;
	int advance_time;

	void addStage(vector<string> &data);
	void addCar(vector<string> &data);

	void setAdvanceTime(int time)
	{
		advance_time = time;
	}
};

//Constructor
CarWash::CarWash()
{
	string command;

	vector<string> data;
	while(getline(cin,command))
	{
		splitBySpace(data,command);

		if(data[0] == "add_stage") addStage(data);

		else if(data[0] == "add_car") addCar(data);

		else if(data[0] == "advance_time") setAdvanceTime(stoi(data[1]));

		data.clear();

		for(int i = 0;i < stages.size();i++)
		{
			stages[i].showWorkers();
			cout  << endl;
		}
	}
}

void CarWash::addStage(vector<string> &data)
{
	Stage newStage;

	for(int i = 1; i < data.size();i++)
	{
		Worker newWorker(stoi(data[i]));
		newStage.addWorker(newWorker);
	}

	stages.push_back(newStage);

	cout << "OK" << endl;
}

void CarWash::addCar(vector<string> &data)
{
	for(int i = 1; i < data.size();i++)
	{
		cars.push_back(Car(stoi(data[i])) );
	}

	cout << "OK" << endl;
}

int main()
{
	CarWash pipleline;
	return 0;
}































