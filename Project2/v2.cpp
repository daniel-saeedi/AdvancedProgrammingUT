#include<iostream>
#include<vector>
#include <sstream>
#include <string>
#include<queue>
using namespace std;

//Functions
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
		car_id = -1;
		isWorking = false;
		_start_work = false;
	}

	bool isOccupied() {return isWorking;}

	//If time_left is less than 0 then return 1
	//1 means the job is done
	bool decrease_time_left(int time)
	{
		time_left -= time;
		if(time_left < 0)
		{
			isWorking = false;
			_start_work = false;
			time_left = 0;
			car_id = -1;
			return 1;
		}
		return 0;
	}

	int get_time_left(){return time_left;}
	int get_car_id(){return car_id;}

	int get_time_coefficient() {return time_coefficient;}

	bool get_start_work(){return _start_work;}

	void set_car_id(int id)
	{
		car_id = id;
	}

	void set_time_left(int time)
	{
		time_left = time;
	}

	void set_working_status(bool status)
	{
		isWorking = status;

	}

	void set_start_work(bool status)
	{
		_start_work = status;
	}

	bool isDone()
	{
		if(time_left == 0) return true;
		return false;
	}
private:
	int time_coefficient;
	int car_id;
	bool isWorking;
	int time_left;
	bool _start_work;
};


class Car
{
public:
	Car(int _luxury_coeff,int _car_id)
	{
		luxury_coefficient = _luxury_coeff;
		worker_id = -1;

		car_id = _car_id;
	}

	void set_worker_id(int id)
	{
		worker_id = id;
	}

	int get_luxury_coefficient(){return luxury_coefficient;}
	int get_worker_id(){return worker_id;}
	int get_car_id(){return car_id;}
	int show_car_info()
	{
		cout << "Luxury coefficient: " << luxury_coefficient << endl;
	}

private:
	int car_id;
	int luxury_coefficient;
	int worker_id;
};

class Stage
{
public:

	void addWorker(Worker *newWorker)
	{
		workers.push_back(newWorker);
	}

	void addToQueue(Car *newCar)
	{
		waitingCars.push(newCar);
	}

	void show_workers_info()
	{
		for(int i = 0;i < workers.size();i++)
		{
			cout << "Worker ID: " << i << endl;
			if(workers[i]->isOccupied())
			{
				int car_id = workers[i]->get_car_id();

				if(car_id != -1)
				{
					cout << "Car ID: " << car_id << endl;
					int car_index = find_car_index(car_id);
					currentlyWashing[car_index]->show_car_info();
					cout << "Time left: " << workers[i]->get_time_left() << endl;
				}
				
			}

			else cout << "Free" << endl;
		}
	}

	void show_waiting_cars(bool label = true)
	{
		queue<Car*> copyOfWaitingCars = waitingCars;
		if(label) cout << "Cars in waiting queue: " << endl;
		while(copyOfWaitingCars.size() > 0)
		{
			cout << "Car ID: " << copyOfWaitingCars.front()->get_car_id() << endl;

			if(!label) cout << "Luxury coefficient: " << copyOfWaitingCars.front()->get_luxury_coefficient() << endl;
			copyOfWaitingCars.pop();
		}
	}

	int get_waiting_cars_size(){return waitingCars.size();}

	vector<Worker*> get_workers() {return workers;}
	Worker* get_worker(int index){return workers[index];}

	void frontCar(int worker_id)
	{
		if(waitingCars.size() > 0)
		{
			Car *front = waitingCars.front();
			waitingCars.pop();

			front->set_worker_id(worker_id);

			currentlyWashing.push_back(front);

			int front_car_luxury = front->get_luxury_coefficient();

			Worker *worker = workers[worker_id];

			worker->set_time_left(front->get_luxury_coefficient()*worker->get_time_coefficient());
			worker->set_working_status(true);
			worker->set_start_work(false);
			worker->set_car_id(front->get_car_id());
		}
	}

	Car* remove_car(int car_id)
	{
		int car_index = 0;
		for(int i = 0;i < currentlyWashing.size();i++)
		{
			if(currentlyWashing[i]->get_car_id() == car_id)
			{
				car_index = i;
				break;
			}
		}

		Car *copyOfCar = currentlyWashing[car_index];
		currentlyWashing.erase(currentlyWashing.begin() + car_index);

		return copyOfCar;
	}

	int find_car_index(int car_id)
	{
		int car_index = 0;
		for(int i = 0;i < currentlyWashing.size();i++)
		{
			if(currentlyWashing[i]->get_car_id() == car_id)
			{
				car_index = i;
				break;
			}
		}

		return car_index;
	}

	bool get_assignWork(){return assignWork;}

	void set_assignWork(bool assign){assignWork = assign;}

private:
	vector<Worker*> workers;
	queue<Car*> waitingCars;
	vector<Car*> currentlyWashing;
	bool assignWork = false;
};

class CarWash
{
public:
	//Constructor
	CarWash();

private:
	vector<Stage*> stages;
	vector<Car*> finished;
	int total_time_passed = 0;
	int _advance_time = 0;
	int total_cars;

	void addStage(vector<string> &data);
	void addCar(vector<string> &data);

	void showStageInfo(int index)
	{
		cout << "Stage ID: " << index << endl;
		stages[index]->show_workers_info();
		stages[index]->show_waiting_cars();
	}

	void set_advance_time(int time)
	{
		total_time_passed += time;
		_advance_time = time;
	}

	int timeNeededForWashing(int luxury_coefficient,int time_coefficient)
	{
		return luxury_coefficient*time_coefficient;
	}

	void workers_status(int stage_no,vector<int> &unoccupied_worker_id,vector<int> &occupied_worker_id)
	{
		vector<Worker*> workers_of_stage = stages[stage_no]->get_workers();
		for(int i = 0;i < workers_of_stage.size();i++)
		{
			if(!workers_of_stage[i]->isOccupied()) unoccupied_worker_id.push_back(i);
			else occupied_worker_id.push_back(i);
		}

	}

	void assign_work(vector<int> &unoccupied_workers_id,int stageNo)
	{
		sort(unoccupied_workers_id.begin(), unoccupied_workers_id.end()); 
		int waitingCarsNumber = stages[stageNo]->get_waiting_cars_size();

		int numberOfWorkAssign = 0;
		int numnerOfUnoccupied = unoccupied_workers_id.size();
		if(waitingCarsNumber > numnerOfUnoccupied) numberOfWorkAssign = numnerOfUnoccupied;
		else numberOfWorkAssign = waitingCarsNumber;
	
		for(int i = 0; i< numberOfWorkAssign;i++)
		{
			stages[stageNo]->frontCar(unoccupied_workers_id[i]);
			stages[stageNo]->get_worker(unoccupied_workers_id[i])->set_working_status(true);
		}
	}

	void move_stage(int car_id,int stageNo)
	{
		Car *car = stages[stageNo]->remove_car(car_id);


		//Finished
		if(stageNo == stages.size() - 1)
		{
			finished.push_back(car);
		}

		else
		{
			stages[stageNo + 1]->addToQueue(car);
		}
	}

	void advance_time()
	{
		for(int time_start = 0; time_start <= _advance_time;time_start++)
		{
			for(int i = 0;i < stages.size();i++)
			{
				vector<int> unoccupied_workers_id;
				vector<int> occupied_workers_id;

				workers_status(i,unoccupied_workers_id,occupied_workers_id);

				int number_of_waiting_cars = stages[i]->get_waiting_cars_size();
				int number_of_unoccupied = unoccupied_workers_id.size();
				int number_of_occupied = occupied_workers_id.size();

				if(time_start > 0)
				{
					for(int j = 0;j < number_of_occupied;j++)
					{
						Worker *worker = stages[i]->get_worker(occupied_workers_id[j]);

						if(worker->get_start_work())
						{
							if(worker->decrease_time_left(1))
							{
								move_stage(worker->get_car_id(),i);
							}
						}

						else
						{
							worker->set_start_work(true);
							
						}
					}
				}

				if(number_of_unoccupied > 0 && number_of_waiting_cars > 0) stages[i]->set_assignWork(true);
				else stages[i]->set_assignWork(false);

				if(time_start > 0 && number_of_unoccupied > 0 && number_of_waiting_cars > 0)
				{
					if(stages[i]->get_assignWork()) assign_work(unoccupied_workers_id,i);
				}

				unoccupied_workers_id.clear();
				occupied_workers_id.clear();
				workers_status(i,unoccupied_workers_id,occupied_workers_id);
				number_of_unoccupied = unoccupied_workers_id.size();
				number_of_occupied = occupied_workers_id.size();

				if(number_of_unoccupied == 0)stages[i]->set_assignWork(false);

			}
		}
	}

	void showFinishedCars()
	{
		for(int i = 0;i< finished.size();i++)
		{
			cout << "Car ID: " <<finished[i]->get_car_id() << endl;
			cout << "Luxury coefficient: " <<finished[i]->get_luxury_coefficient() << endl;
		}
	}

	void showAllWaitingCars()
	{
		for(int i = 0;i < stages.size();i++)
		{
			stages[i]->show_waiting_cars(false);
		}
	}

	void show_carwash_info()
	{
		cout << "Passed time: " << total_time_passed << endl;
		cout << "Cars waiting: " << endl;
		showAllWaitingCars();
		cout << "Stages info: " << endl;
		for(int i = 0;i < stages.size();i++)
		{
			showStageInfo(i);
		}
		cout << "Cars finished: " << endl;
		showFinishedCars();
	}

	void finish()
	{
		while(!isFinished())
		{
			set_advance_time(1);
			advance_time();
		}
	}

	bool isFinished()
	{
		if(total_cars == finished.size()) return true;
		return false;
	}
};

CarWash::CarWash()
{
	total_cars = 0;
	string command;

	vector<string> data;
	while(getline(cin,command))
	{
		splitBySpace(data,command);

		if(data[0] == "add_stage") addStage(data);

		else if(data[0] == "add_car")
		{
			addCar(data);
			total_cars++;
		}

		else if(data[0] == "advance_time")
		{
			set_advance_time(stoi(data[1]));
			advance_time();
			cout << "OK" << endl;
		}

		else if(data[0] == "show_stage_info")
		{
			showStageInfo(stoi(data[1]));
		}

		else if(data[0] == "show_carwash_info")
		{
			show_carwash_info();
		}

		else if(data[0] == "finish")
		{
			finish();
			cout << "OK" << endl;
		}

		else cout << "Wrong Command" << endl;

		data.clear();

	}
}

void CarWash::addStage(vector<string> &data)
{
	Stage *new_stage;

	new_stage = new Stage();

	for(int i = 2; i < data.size();i++)
	{
		Worker *new_worker = new Worker(stoi(data[i]));
		new_stage->addWorker(new_worker);
	}

	stages.push_back(new_stage);

	cout << "OK" << endl;
}

void CarWash::addCar(vector<string> &data)
{
	if(stages.size() == 0) 
		cout << "Please add a stage first!" << endl;

	else
	{
		int car_id = stages[0]->get_waiting_cars_size();
		stages[0]->addToQueue(new Car(stoi(data[1]), car_id));
		cout << "OK" << endl;
	}
}

int main()
{
	CarWash pipleline;
	return 0;
}