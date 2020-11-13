#include "Game.hpp"
#include<iostream>
#include "rsdl.hpp"

using namespace std;

int main()
{
	Window* window = new Window(1024,600,"Soccer Stars!!!");
	Game SoccerStars(1024,600,window);
}