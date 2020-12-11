#include<iostream>
#include "Game.hpp"
#include "rsdl.hpp"
using namespace std;
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 480
#define THROW_RADIUS 30
#define MAX_INTIAL_SPEED 700

int main()
{
	Window* window = new Window(WINDOW_WIDTH,WINDOW_HEIGHT,"Super Soccer Stars!!!");
	Game SoccerStars(THROW_RADIUS,MAX_INTIAL_SPEED,WINDOW_WIDTH,WINDOW_HEIGHT,window);
	SoccerStars.StartGame();
}