#include "Game.hpp"
#define PLAYERS 5
#define BALL 0
#define TEAM_A 1
#define TEAM_B 2

#include<vector>
//Constructor
Game::Game(int width,int height, Window* _window)
{
	SetPreloadPositions();
	stadium = new Stadium(width,height);
	teamA = new Team(CreatePlayers(TEAM_A));
	teamB = new Team(CreatePlayers(TEAM_B));
	background_image = "Assets/field.jpg";
	window = _window;
	ball = new Ball(preload_position[BALL][0].x,preload_position[BALL][0].y);
	Draw();
}

void Game::SetPreloadPositions()
{
	//Poisition of Ball
	preload_position[BALL].push_back(Point(200,200));

	//Poisition of team A players
	preload_position[TEAM_A].push_back(Point(20,20));
	preload_position[TEAM_A].push_back(Point(100,20));
	preload_position[TEAM_A].push_back(Point(20,200));
	preload_position[TEAM_A].push_back(Point(350,50));
	preload_position[TEAM_A].push_back(Point(400,50));
	
	//Poisition of team B players
	preload_position[TEAM_B].push_back(Point(500,500));
	preload_position[TEAM_B].push_back(Point(200,500));
	preload_position[TEAM_B].push_back(Point(300,500));
	preload_position[TEAM_B].push_back(Point(600,500));
}

std::vector<Player*> Game::CreatePlayers(int team_id)
{
	std::vector<Player*> players;
	for(int i = 0;i < PLAYERS;i++)
	{
		int pos_x = preload_position[team_id][i].x;
		int pos_y = preload_position[team_id][i].y;
		players.push_back(new Player(pos_x,pos_y,team_id));
	}

	return players;
}

void Game::Update()
{
	while(window->has_pending_event())
	{
		Event e = window->poll_for_event();
		switch(e.get_type())
		{
			case Event::EventType::QUIT:
				exit(0);
				break;
		}
	}
}

void Game::Draw()
{
	while(true)
	{
		//Draw Background
		window->draw_img(background_image, Rectangle(0,0,stadium->get_width(),stadium->get_height()));
		//Draw Ball
		DrawBall();
		//Draw Player
		DrawPlayer(TEAM_A);
		DrawPlayer(TEAM_B);
		window->update_screen();
		Update();
		delay(15);
	}
}

void Game::DrawBall()
{
	std::string img_src = ball->get_ball_image();
	int pos_x = ball->get_position_x();
	int pos_y = ball->get_position_y();
	int width = ball->get_width();
	int height = ball->get_height();

	window->draw_img(img_src, Rectangle(pos_x,pos_y,width,height));
}

void Game::DrawPlayer(int team_id)
{
	Team* team;
	if(team_id == TEAM_A) team = teamA;
	if(team_id == TEAM_B) team = teamB;

	for(int i = 0;i < team->players_size();i++)
	{
		std::string img_src = team->get_player(i)->get_player_image();
		int pos_x = team->get_player(i)->get_position_x();
		int pos_y = team->get_player(i)->get_position_y();
		int width = team->get_player(i)->get_width();
		int height = team->get_player(i)->get_height();
		window->draw_img(img_src, Rectangle(pos_x,pos_y,width,height));
	}
}








