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
	Player *selected_player;
	std::map<int,std::vector<Point>> preload_position;
	int throw_radius;
	int max_initial_speed;

	std::vector<Player*> CreatePlayers(int team_id);
	void Update();
	void Draw();
	void DrawBall();
	void DrawPlayer(int team_id);
	void SetPreloadPositions();
	void SelectPawn(int team_id,Point mouse_position);
	bool IsSelected(int width,int height,int pos_x,int pos_y,Point mouse_position);
	void StartMove(Event e,Player *player);
	void MoveObjects();


	Point SubtractVector(Point vector1,Point vector2);
	int VectorSize(Point vector);
	Point CalculateVelocity(Point d,int d_size);

};

#endif