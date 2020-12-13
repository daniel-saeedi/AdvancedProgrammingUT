#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H
#include "Utunes.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class CommandHandler
{
public:
	CommandHandler();
	void run();
private:
	vector<string> tokenize_input(string input);
};
#endif