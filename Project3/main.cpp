#include "Game.hpp"
#include<iostream>
#include "rsdl.hpp"

using namespace std;

int main()
{
	Window* window = new Window(800,480,"Soccer Stars!!!");
	Game SoccerStars(800,480,window);
}