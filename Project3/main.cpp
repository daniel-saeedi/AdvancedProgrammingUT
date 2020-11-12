#include "Game.hpp"
#include<iostream>
#include "rsdl.hpp"

using namespace std;

int main()
{
	Window* window = new Window(1199,598,"Soccer Stars!!!");
	Game SoccerStars(1199,598,window);
}