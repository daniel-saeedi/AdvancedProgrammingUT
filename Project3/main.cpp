#include "Game.hpp"
#include<iostream>
#include "rsdl.hpp"
using namespace std;
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 480
int main()
{
	Window* window = new Window(WINDOW_WIDTH,WINDOW_HEIGHT,"Super Soccer Stars!!!");
	Game SoccerStars(WINDOW_WIDTH,WINDOW_HEIGHT,window);
}