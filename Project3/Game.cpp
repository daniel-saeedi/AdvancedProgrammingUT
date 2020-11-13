#include "Game.hpp"
#include<cmath>
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
	selected_player = nullptr;
	throw_radius = 60;
	max_initial_speed = 1000;
	Draw();
}

void Game::SetPreloadPositions()
{
	//Poisition of Ball
	preload_position[BALL].push_back(Point(495,280));

	//Poisition of team A players
	preload_position[TEAM_A].push_back(Point(20,260));
	preload_position[TEAM_A].push_back(Point(180,120));
	preload_position[TEAM_A].push_back(Point(180,400));
	preload_position[TEAM_A].push_back(Point(350,200));
	preload_position[TEAM_A].push_back(Point(350,320));
	
	//Poisition of team B players
	preload_position[TEAM_B].push_back(Point(920,260));
	preload_position[TEAM_B].push_back(Point(780,120));
	preload_position[TEAM_B].push_back(Point(780,400));
	preload_position[TEAM_B].push_back(Point(610,200));
	preload_position[TEAM_B].push_back(Point(610,320));
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
	bool is_mouse_down = false;
	while(window->has_pending_event())
	{
		Event e = window->poll_for_event();
		switch(e.get_type())
		{
			case Event::EventType::QUIT:
			{
				exit(0);
				break;
			}
				
			case Event::EventType::LCLICK:
			{
				Point mouse_position = e.get_mouse_position();
				SelectPawn(TEAM_A,mouse_position);
				SelectPawn(TEAM_B,mouse_position);
				is_mouse_down = true;
			}

			case Event::EventType::LRELEASE:
			{
				if(selected_player != nullptr && !is_mouse_down)
				{
					StartMove(e,selected_player);
					selected_player = nullptr;
				}

				is_mouse_down = false;
			}
		}
	}
}

Point Game::SubtractVector(Point vector1,Point vector2)
{
	Point subtract;
	subtract.x = vector1.x - vector2.x;
	subtract.y = vector1.y - vector2.y;
	return subtract;
}

int Game::VectorSize(Point vector)
{
	return sqrt(pow(vector.x,2)+pow(vector.y,2));
}

void Game::StartMove(Event e,Player *player)
{
	Point mouse_position = e.get_mouse_position();
	Point pawn_position;
	pawn_position.x = player->get_center_x();
	pawn_position.y = player->get_center_y();
	Point d = SubtractVector(mouse_position,pawn_position);
	int d_size = VectorSize(d);
	Point velocity = CalculateVelocity(d,d_size);
	player->set_vx(velocity.x);
	player->set_vy(velocity.y); 
}

Point Game::CalculateVelocity(Point d,int d_size)
{
	Point v;
	int denominator;
	if(d_size < throw_radius) denominator = throw_radius;
	else denominator = d_size;

	v.x = ((-1)*d.x*max_initial_speed)/denominator;
	v.y = ((-1)*d.y*max_initial_speed)/denominator;
	return v;
}

void Game::SelectPawn(int team_id,Point mouse_position)
{
	Team* team;
	if(team_id == TEAM_A) team = teamA;
	if(team_id == TEAM_B) team = teamB;

	for(int i = 0;i < team->players_size();i++)
	{
		int width = team->get_player(i)->get_width();
		int height = team->get_player(i)->get_height();
		int pos_x = team->get_player(i)->get_position_x();
		int pos_y = team->get_player(i)->get_position_y();

		if(IsSelected(width,height,pos_x,pos_y,mouse_position))
		{
			selected_player = team->get_player(i);
		}
	}
}

bool Game::IsSelected(int width,int height,int pos_x,int pos_y,Point mouse_position)
{
	int mouse_x = mouse_position.x;
	int mouse_y = mouse_position.y;
	return mouse_x >= pos_x && mouse_y >= pos_y &&
		   mouse_x <= pos_x + width && mouse_y <= pos_y + height;
}

void Game::MoveObjects()
{
	for(int i = 0;i < PLAYERS;i++)
	{
		
		teamA->get_player(i)->MovePlayer(0.015);
		stadium->CollideWithEdges(teamA->get_player(i));

		teamB->get_player(i)->MovePlayer(0.015);
		stadium->CollideWithEdges(teamB->get_player(i));
	}
}

void Game::Draw()
{
	while(true)
	{
		window->clear();
		MoveObjects();
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

