#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<map>
#include "Object.hpp"
#include "Stadium.hpp"
#include "Player.hpp"
#include "Ball.hpp"
#include "Team.hpp"
#include "rsdl.hpp"
#include "functions.hpp"

class Game
{
public:
	Game(int _width,int _height, Window* _window);

private:
	Team* teamA;
	Team* teamB;
	std::string background_image;
	Window *window;
	Ball *ball;
	Player *selected_player;
	std::map<int,std::vector<Point>> preload_position;
	int throw_radius;
	int max_initial_speed;
	int width;
	int height;

	std::vector<Player*> CreatePlayers(int team_id);
	void Update();
	void Draw();
	void DrawBall();
	void DrawPlayer(int team_id);
	void DrawBackground();
	void SetPreloadPositions();
	void SelectPawn(int team_id,Point mouse_position);
	bool IsSelected(int radius,int pos_x,int pos_y,Point mouse_position);
	void StartMove(Event e,Player *player);
	void MoveObjects();

	bool Collision(Object *object1,Object *object2);
	bool CollisionDetector(Object *object1,Object *object2);
	std::vector<Point> CalculateCollisionVelocity(Object *object1,Object *object2);
	Point CalculateVelocity(Point d,int d_size);
};

#endif