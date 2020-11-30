#include<iostream>
#include "src/CommandHandler.hpp"
using namespace std;

int main()
{
	CommandHandler command_handler = CommandHandler();
	command_handler.run();
	return 0;
}