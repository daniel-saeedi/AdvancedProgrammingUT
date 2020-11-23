#ifndef GAME_H
#define GAME_H
#include<iostream>
#include<map>
#include "Physics.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include "Ball.hpp"
#include "Team.hpp"
#include "rsdl.hpp"
#include "functions.hpp"

class Game : public Physics
{
public:
	Game(int _throw_radius,int _max_initial_speed,int _width,int _height, Window* _window);
	void StartGame();
private:
	Window *window;
	Team* teamA;
	Team* teamB;
	std::string background_image;
	Ball *ball;
	Player *selected_player;
	std::map<int,std::vector<Point>> preload_position;
	int turn;
	int goal_status;
	int goal_per_round;
	int rounds;
	int goal_team_A;
	int goal_team_B;
	bool finished;
	int winner;
	bool is_mouse_down;

	std::vector<Player*> CreatePlayers(int team_id);
	void SetPreloadPositions();
	void SelectPawn(int team_id,Point mouse_position);
	bool IsSelected(int radius,int pos_x,int pos_y,Point mouse_position);
	void StartMove(Event e,Player *player);
	void MoveObjects();
	void GameStatus();
	void Reset();
	void ResetPlayerPosition(int team_id);

	//Screens
	int GetInput(std::string filed_name);
	void DrawHeader();
	void ShowGame();
	void ShowFinishedScreen();
	void Update();
	void LeftClick(Event e);
	void LeftRelease(Event e);
	void Draw();
	void DrawBall();
	void DrawPlayer(int team_id);
	void DrawBackground();
	void DrawStars();
};

#endif