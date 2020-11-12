#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<map>
#include "Stadium.hpp"
#include "Player.hpp"
#include "Ball.hpp"
#include "Team.hpp"
#include "rsdl.hpp"

class Game
{
public:
	Game(int width,int height, Window* _window);

private:
	Stadium *stadium;
	Team* teamA;
	Team* teamB;
	std::string background_image;
	Window *window;
	Ball *ball;
	std::map<int,std::vector<Point>> preload_position;

	std::vector<Player*> CreatePlayers(int team_id);
	void Update();
	void Draw();
	void DrawBall();
	void DrawPlayer(int team_id);
	void SetPreloadPositions();
	// void Update();
	// void Process();
	// void Render();
};

#endif