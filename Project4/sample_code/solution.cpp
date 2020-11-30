#include <vector>
#include <iostream>
#include <string>
#include <iterator>
#include <sstream>

using namespace std;

constexpr char CAR_ID[] = "Car ID: ";
constexpr char WORKER_ID[] = "Worker ID: ";
constexpr char STAGE_ID[] = "Stage ID: ";
constexpr char TIME_LEFT[] = "Time left: ";
constexpr char LUXURY_COEF[] = "Luxury coefficient: ";
constexpr char FREE[] = "Free";
constexpr char CARS_IN_WATING_QUEUE[] = "Cars in waiting queue: ";
constexpr char OK[] = "OK";
constexpr char CARS_WAITING[] = "Cars waiting: ";
constexpr char STAGES_INFO[] = "Stages info: ";
constexpr char CARS_FINISHED[] = "Cars finished: ";
constexpr char PASSED_TIME[] = "Passed time: ";
constexpr char ADD_STAGE[] = "add_stage";
constexpr char ADD_CAR[] = "add_car";
constexpr char ADVANCE_TIME[] = "advance_time";
constexpr char FINISH_ALL[] = "finish";
constexpr char SHOW_STAGE_INFO[] = "show_stage_info";
constexpr char SHOW_CARWASH_INFO[] = "show_carwash_info";

constexpr int FIRST_ID = 0;


class Car
{

public:
    Car(int coef);
    void set_id(int _id);
    int get_coef();
    void show_info();

private:
    unsigned int id;
    int luxury_coef;
};

Car::Car(int coef)
: luxury_coef(coef)
{
}

void Car::set_id(int _id)
{
    id = _id;
}

int Car::get_coef()
{
    return luxury_coef;
}

void Car::show_info()
{
    cout << CAR_ID << id << endl;
    cout << LUXURY_COEF << luxury_coef << endl;
}

class Worker
{

public:
    Worker(int _coef);
    void set_id(int _id);
    bool is_free();
    void advance_time();
    void set_car(Car* _car);
    void show_info();
    bool is_done();
    Car* exit_car();
private:
    unsigned int id;
    int time_coef;
    int time_left;
    Car* car;
};

Worker::Worker(int _coef)
: time_coef(_coef)
, car(nullptr)
{
}

void Worker::set_id(int _id)
{
    id = _id;
}

bool Worker::is_free()
{
    return car == nullptr;
}

void Worker::advance_time()
{
    if (time_left > 0)
        time_left--;
}

void Worker::set_car(Car* _car)
{
    car = _car;
    time_left = time_coef * _car->get_coef();
}

void Worker::show_info()
{
    cout << WORKER_ID << id << endl;
    if (is_free())
        cout << FREE << endl;
    else {
        car->show_info();
        cout << TIME_LEFT << time_left << endl;
    }
}

bool Worker::is_done()
{
    return time_left <= 0;
}

Car* Worker::exit_car() 
{
    if (this->is_done())
    {
        Car* temp = car;
        car = nullptr;
        return temp;
    }

    return nullptr;
}

class Stage
{

public:
    Stage();
    void set_id(int _id);
    void set_workers_id(int next_worker_id);
    unsigned int get_workers_size();
    void add_car(Car* car);
    void add_worker(Worker* worker);
    void show_info();
    void advance_time();
    Car* exit_finished_car();

private:
    Worker* get_first_free_worker();

    unsigned int id;
    std::vector<Worker*> workers;
    std::vector<Car*> waiting_queue;
};

Stage::Stage()
{
}

void Stage::set_id(int _id)
{
    id = _id;
}

Worker* Stage::get_first_free_worker()
{
    for (size_t i = 0; i < workers.size(); i++)
    {
        if (workers[i]->is_free())
            return workers[i];
    }
    return nullptr;
}

void Stage::set_workers_id(int next_worker_id)
{
    for (size_t i = 0; i < workers.size(); i++)
        workers[i]->set_id(next_worker_id++);
}

unsigned int Stage::get_workers_size()
{
    return workers.size();
}

void Stage::add_worker(Worker* worker)
{
    workers.push_back(worker);
}

void Stage::show_info()
{
    cout << STAGE_ID << id << endl;
    for (size_t i = 0; i < workers.size(); i++)
        workers[i]->show_info();

    cout << CARS_IN_WATING_QUEUE << endl;
    for (size_t i = 0; i < waiting_queue.size(); i++)
        waiting_queue[i]->show_info();
}

void Stage::advance_time()
{
    for (size_t i = 0; i < workers.size(); i++)
        workers[i]->advance_time();

    if (waiting_queue.size() > 0)
    {
        Worker* free_worker = get_first_free_worker();
        if (free_worker)
        {
            free_worker->set_car(waiting_queue[0]);
            waiting_queue.erase(waiting_queue.begin());
        }
    }
}

Car* Stage::exit_finished_car()
{
    for (size_t i = 0; i < workers.size(); i++)
    {
        if (!workers[i]->is_free() && workers[i]->is_done())
        {
            return workers[i]->exit_car();
        }
    }
    return nullptr;
}

void Stage::add_car(Car* car)
{
    waiting_queue.push_back(car);
}

class Carwash
{

public:
    Carwash();
    void add_stage(Stage* stage);
    void add_car(Car* car);
    void finish_car(Car* car);
    void advance_time_steps(size_t time_step);
    void finish_all();
    void show_stage_info(int stage_id);
    void show_carwash_info();

private:
    void advance_time();
    void show_passed_time();
    void show_waiting_cars_info();
    void show_stages_info();
    void show_finished_cars_info();
    
    unsigned int next_car_id;
    unsigned int next_stage_id;
    unsigned int next_worker_id;
    int passed_time;
    std::vector<Stage*> stages;
    std::vector<Car*> waiting_cars_queue;
    std::vector<Car*> finished_cars;
};

Carwash::Carwash()
: next_car_id(FIRST_ID)
, next_stage_id(FIRST_ID)
, next_worker_id(FIRST_ID)
, passed_time(0)
{
}

void Carwash::add_stage(Stage* stage)
{
    stage->set_id(next_stage_id++);
    stage->set_workers_id(next_worker_id);
    next_worker_id += stage->get_workers_size();
    stages.push_back(stage);
}

void Carwash::add_car(Car* car)
{
    car->set_id(next_car_id++);
    waiting_cars_queue.push_back(car);
}

void Carwash::finish_car(Car* car)
{
    finished_cars.push_back(car);
}

void Carwash::advance_time_steps(size_t time_step)
{
    for (size_t i = 0; i < time_step; i++)
        advance_time();
}

void Carwash::advance_time()
{
    if (waiting_cars_queue.size() > 0)
    {
        stages[0]->add_car(waiting_cars_queue[0]);
        waiting_cars_queue.erase(waiting_cars_queue.begin());
    }

    for (int i = stages.size() - 1; i >= 0; i--)
    {
        Car* exited_car = stages[i]->exit_finished_car();
        if (exited_car)
        {
            if (i == (int)stages.size() - 1)
                finished_cars.push_back(exited_car);
            else
                stages[i+1]->add_car(exited_car);
        }
    }

    for (size_t i = 0; i < stages.size(); i++)
        stages[i]->advance_time();

    passed_time++;
}

void Carwash::finish_all()
{
    while (finished_cars.size() != next_car_id)
        advance_time();
}

void Carwash::show_stage_info(int stage_id)
{
    stages[stage_id]->show_info();
}

void Carwash::show_waiting_cars_info()
{
    cout << CARS_WAITING << endl;
    for (size_t i = 0; i < waiting_cars_queue.size(); i++)
        waiting_cars_queue[i]->show_info();
}
void Carwash::show_stages_info()
{
    cout << STAGES_INFO<< endl;
    for (size_t i = 0; i < stages.size(); i++)
        stages[i]->show_info();
}
void Carwash::show_finished_cars_info()
{
    cout << CARS_FINISHED << endl;
    for (size_t i = 0; i < finished_cars.size(); i++)
        finished_cars[i]->show_info();
}

void Carwash::show_passed_time()
{
    cout << PASSED_TIME << passed_time << endl;
}

void Carwash::show_carwash_info()
{
    show_passed_time();
    show_waiting_cars_info();
    show_stages_info();
    show_finished_cars_info();
}

class CommandHandler
{

public:
    CommandHandler();
    void run();

private:
    std::vector<std::string> tokenize_input(std::string input);
    Car* create_car(std::string input);
    Stage* create_stage(std::string input);
    size_t get_time_steps(std::string input);
    int get_object_id(std::string input);

    Carwash* carwash;
};

CommandHandler::CommandHandler()
: carwash(new Carwash())
{
}

void CommandHandler::run()
{
    const int COMMAND_TYPE_INDEX = 0;
    string input;
    while (getline(cin, input)) 
    {
        const string command_type = tokenize_input(input)[COMMAND_TYPE_INDEX];

        if (command_type == ADD_STAGE)
        {
            carwash->add_stage(create_stage(input));
            cout << OK << endl;
        }
        else if (command_type == ADD_CAR)
        {
            carwash->add_car(create_car(input));
            cout << OK << endl;
        }
        else if (command_type == ADVANCE_TIME)
        {
            carwash->advance_time_steps(get_time_steps(input));
            cout << OK << endl;
        }
        else if (command_type == FINISH_ALL)
        {
            carwash->finish_all();
            cout << OK << endl;
        }
        else if (command_type == SHOW_STAGE_INFO)
            carwash->show_stage_info(get_object_id(input));
        else if (command_type == SHOW_CARWASH_INFO)
            carwash->show_carwash_info();
    }
}

vector<string> CommandHandler::tokenize_input(string input)
{
    stringstream input_string_stream(input);
    return vector<string>(istream_iterator<string>(input_string_stream),
                          istream_iterator<string>());
}

Stage* CommandHandler::create_stage(string input) 
{
    const int WORKERS_COUNT_INDEX = 1;
    const int FIRST_WORKER_COEF_INDEX = 2;

    vector<string> tokenized_input = tokenize_input(input);
    
    Stage* new_stage = new Stage();
    for (int i = 0; i < stoi(tokenized_input[WORKERS_COUNT_INDEX]); i++)
    {
        Worker* worker = new Worker(stoi(tokenized_input[FIRST_WORKER_COEF_INDEX + i]));
        new_stage->add_worker(worker);
    }
    return new_stage;
}

Car* CommandHandler::create_car(string input)
{
    const int CAR_COEF_INDEX = 1;

    vector<string> tokenized_input = tokenize_input(input);
    Car* new_car = new Car(stoi(tokenized_input[CAR_COEF_INDEX]));
    return new_car;

}

size_t CommandHandler::get_time_steps(string input) 
{
    const int TIME_STEPS_INDEX = 1;

    return (size_t)stoi(tokenize_input(input)[TIME_STEPS_INDEX]);
}

int CommandHandler::get_object_id(string input) 
{
    const int ID_INDEX = 1;

    return stoi(tokenize_input(input)[ID_INDEX]);
}

int main() 
{
    CommandHandler command_handler = CommandHandler();
    command_handler.run();
    return 0;
}