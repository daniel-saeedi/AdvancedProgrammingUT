#include "Game.hpp"
#include "Object.hpp"
#include "TextInput.hpp"
#include<cmath>
#define PLAYERS 5
#define BALL 0
#define TEAM_A 1
#define TEAM_B 2
#define PLAYER_RADIUS 30
#define PLAYER_MASS 1
#define BALL_RADIUS 14
#define BALL_MASS 1
#define FRAME_RATE 0.015
#include<vector>
//Constructor
Game::Game(int _width,int _height, Window* _window)
{
	goal_status = 0;
	goal_team_A = 0;
	goal_team_B = 0;
	selected_player = nullptr;
	throw_radius = 60;
	max_initial_speed = 700;
	width = _width;
	height = _height;
	finished = false;
	winner = 0;
	background_image = "Assets/field.jpg";
	window = _window;
	turn = TEAM_A;

	SetPreloadPositions();
	teamA = new Team(CreatePlayers(TEAM_A));
	teamB = new Team(CreatePlayers(TEAM_B));
	ball = new Ball(preload_position[BALL][0].x,preload_position[BALL][0].y,BALL_RADIUS,BALL_MASS);
	rounds = GetInput("Rounds");
	goal_per_round = GetInput("Goal Per Round");
	Draw();
}

void Game::SetPreloadPositions()
{
	//Poisition of Ball
	preload_position[BALL].push_back(Point(390,220));
	//Poisition of team A players
	preload_position[TEAM_A].push_back(Point(50,240));
	preload_position[TEAM_A].push_back(Point(160,120));
	preload_position[TEAM_A].push_back(Point(160,360));
	preload_position[TEAM_A].push_back(Point(300,190));
	preload_position[TEAM_A].push_back(Point(300,290));
	//Poisition of team B players
	preload_position[TEAM_B].push_back(Point(750,240));
	preload_position[TEAM_B].push_back(Point(640,120));
	preload_position[TEAM_B].push_back(Point(640,360));
	preload_position[TEAM_B].push_back(Point(500,190));
	preload_position[TEAM_B].push_back(Point(500,290));
}

std::vector<Player*> Game::CreatePlayers(int team_id)
{
	std::vector<Player*> players;
	for(int i = 0;i < PLAYERS;i++)
	{
		int pos_x = preload_position[team_id][i].x;
		int pos_y = preload_position[team_id][i].y;
		players.push_back(new Player(pos_x,pos_y,PLAYER_RADIUS,PLAYER_MASS,team_id));
	}
	return players;
}

void Game::Draw()
{
	while(true)
	{
		window->clear();
		Update();
		if(finished) ShowFinishedScreen();
		else ShowGame();
		delay(FRAME_RATE*1000);
	}
}

int Game::GetInput(std::string filed_name)
{
	try
	{
		TextInputWindow textInputWindow(width,height,filed_name,window);
		textInputWindow.display();
		return stoi(textInputWindow.getText());
	}
	catch(string exception)
	{
		cerr << "EXCEPTION: " << exception << endl;
		exit(1);
	}
}

void Game::ShowGame()
{
	MoveObjects();
	GameStatus();
	//Draw Background
	DrawBackground();
	//Draw Header
	DrawHeader();
	//Draw Ball
	DrawBall();
	//Draw Player
	DrawPlayer(TEAM_A);
	DrawPlayer(TEAM_B);
	DrawStars();
	window->update_screen();
}

void Game::DrawStars()
{
	Team *team;
	if(turn == TEAM_A) team = teamA;
	if(turn == TEAM_B) team = teamB;
	for(int i = 0;i < PLAYERS;i++)
	{
		int x = team->get_player(i)->get_x() - 30;
		int y = team->get_player(i)->get_y() - 30;
		window->draw_img("Assets/star.png", Rectangle(x,y,60,60));
	}
}
void Game::DrawHeader()
{
	window->draw_img("Assets/header.png", Rectangle(0,0,width,50));
	window->show_text("Team A   Goals: "+std::to_string(teamA->get_total_goals()),Point(10,10),WHITE,"./Assets/FreeSans.ttf", 20);
	window->show_text("Goals: "+std::to_string(teamB->get_total_goals()) + "   Team B",Point(width-200,10),WHITE,"./Assets/FreeSans.ttf", 20);
}

void Game::ShowFinishedScreen()
{
	window->draw_rect(Rectangle(0,0,width,height), BLACK);
	std::string message = "Team ";
	std::string goals   = "Goals: ";
	std::string rounds   = "Rounds: ";
	if(winner == TEAM_A)
	{
		message += "A won!";
		goals   += std::to_string(teamA->get_total_goals());
		rounds  += std::to_string(teamA->get_won_rounds());
	}
	else if(winner == TEAM_B)
	{
		message += "B won!";
		goals   += std::to_string(teamB->get_total_goals());
		rounds  += std::to_string(teamB->get_won_rounds());
	}
	window->show_text(message, Point(250, 150), WHITE, "./Assets/FreeSans.ttf", 50);
	window->show_text(goals, Point(320, 220), WHITE, "./Assets/FreeSans.ttf", 30);
	window->show_text(rounds, Point(320, 270), WHITE, "./Assets/FreeSans.ttf", 30);
	window->update_screen();
}

void Game::GameStatus()
{
	if(goal_status != 0 && !finished)
	{	
		if(goal_status == TEAM_A)
		{
			goal_team_B++;
			teamB->increase_total_goals();
		}
		if(goal_status == TEAM_B)
		{
			goal_team_A++;
			teamA->increase_total_goals();
		}
		goal_status = 0;
		Reset();
		if(goal_team_A >= goal_per_round || goal_team_B >= goal_per_round)
		{
			if(goal_team_A >= goal_per_round)
			{
				teamA->increase_won_rounds();
			}
			else
			{
				teamB->increase_won_rounds();
			}
			goal_team_A = 0,goal_team_B = 0;
		}
	}

	if(teamA->get_won_rounds() >= ceil(rounds/2.0))
	{
		finished = true;
		winner = TEAM_A;
	}
	else if(teamB->get_won_rounds() >= ceil(rounds/2.0))
	{
		finished = true;
		winner = TEAM_B;
	}
}

void Game::DrawBackground()
{
	window->draw_img(background_image, Rectangle(0,0,width,height));
}

void Game::Reset()
{
	ball->set_x(preload_position[BALL][0].x);
	ball->set_y(preload_position[BALL][0].y);
	ball->set_vx(0);
	ball->set_vy(0);
	ResetPlayerPosition(TEAM_A);
	ResetPlayerPosition(TEAM_B);
}

void Game::ResetPlayerPosition(int team_id)
{
	Team *team;
	if(team_id == TEAM_A) team = teamA;
	else if(team_id == TEAM_B) team = teamB;
	for(int i = 0;i < PLAYERS;i++)
	{
		int pos_x = preload_position[team_id][i].x;
		int pos_y = preload_position[team_id][i].y;
		team->get_player(i)->set_x(pos_x);
		team->get_player(i)->set_y(pos_y);
		team->get_player(i)->set_vx(0);
		team->get_player(i)->set_vy(0);
	}
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
				LeftClick(is_mouse_down,e);
			}

			case Event::EventType::LRELEASE:
			{
				LeftRelease(is_mouse_down,e);
			}
		}
	}
}

void Game::LeftClick(bool &is_mouse_down,Event e)
{
	Point mouse_position = e.get_mouse_position();
	if(turn == TEAM_A) SelectPawn(TEAM_A,mouse_position);
	else SelectPawn(TEAM_B,mouse_position);
	is_mouse_down = true;
}

void Game::LeftRelease(bool &is_mouse_down,Event e)
{
	if(selected_player != nullptr && !is_mouse_down)
	{
		StartMove(e,selected_player);
		selected_player = nullptr;
		if(turn == TEAM_A) turn = TEAM_B;
		else turn = TEAM_A;
	}

	is_mouse_down = false;
}
void Game::DrawBall()
{
	std::string img_src = ball->get_ball_image();
	int pos_x = ceil(ball->get_x());
	int pos_y = ceil(ball->get_y());
	int radius = ball->get_radius();

	window->draw_img(img_src, Rectangle(pos_x,pos_y,radius*2,radius*2));
}

void Game::DrawPlayer(int team_id)
{
	Team* team;
	if(team_id == TEAM_A) team = teamA;
	if(team_id == TEAM_B) team = teamB;
	for(int i = 0;i < team->players_size();i++)
	{
		std::string img_src = team->get_player(i)->get_player_image();
		int pos_x = ceil(team->get_player(i)->get_x());
		int pos_y = ceil(team->get_player(i)->get_y());
		int radius = team->get_player(i)->get_radius();
		window->draw_img(img_src, Rectangle(pos_x-radius,pos_y-radius,radius*2,radius*2));
	}
}

void Game::StartMove(Event e,Player *player)
{
	Point mouse_position = e.get_mouse_position();
	Point pawn_position;
	pawn_position.x = player->get_x();
	pawn_position.y = player->get_y();
	Point d = SubtractVector(mouse_position,pawn_position);
	int d_size = VectorSize(d);
	Point velocity = CalculateVelocity(d,d_size);
	player->set_vx(velocity.x);
	player->set_vy(velocity.y); 
}

void Game::SelectPawn(int team_id,Point mouse_position)
{
	Team* team;
	if(team_id == TEAM_A) team = teamA;
	if(team_id == TEAM_B) team = teamB;

	for(int i = 0;i < team->players_size();i++)
	{
		int radius = team->get_player(i)->get_radius();
		int pos_x = team->get_player(i)->get_x();
		int pos_y = team->get_player(i)->get_y();

		if(IsSelected(radius,pos_x,pos_y,mouse_position))
		{
			selected_player = team->get_player(i);
		}
	}
}

bool Game::IsSelected(int radius,int pos_x,int pos_y,Point mouse_position)
{
	int mouse_x = mouse_position.x;
	int mouse_y = mouse_position.y;
	return pow(radius,2)-(pow(pos_x-mouse_x,2) + pow(pos_y-mouse_y,2)) >= 0;
}

void Game::MoveObjects()
{
	ball->Move(FRAME_RATE);
	goal_status = ball->CollideWithEdges(width,height);
	bool collided_players = false;
	for(int i = 0;i < PLAYERS;i++)
	{
		for(int j = 0;j < PLAYERS;j++)
		{
			collided_players = Collision(teamA->get_player(i),teamA->get_player(j))
			|| Collision(teamA->get_player(i),teamB->get_player(j))
			|| Collision(teamB->get_player(i),teamB->get_player(j));
		}
		Collision(teamA->get_player(i),ball);
		Collision(teamB->get_player(i),ball);
		teamA->get_player(i)->CollideWithEdges(width,height);
		teamB->get_player(i)->CollideWithEdges(width,height);

		if(!collided_players)
		{
			teamA->get_player(i)->Move(FRAME_RATE);
			teamB->get_player(i)->Move(FRAME_RATE);
		}
		collided_players = false;
	}
	
}

bool Game::CollisionDetector(Object *object1,Object *object2)
{
	if(object1 != object2)
	{
		double r1 = object1->get_radius();
		double r2 = object2->get_radius();
		Point distance;
		distance.x = object2->get_x() - object1->get_x();
		distance.y = object2->get_y() - object1->get_y();
		double d = VectorSize(distance);
		if(d < r1+r2) return true;
		else return false;
	}
	else return false;
}

bool CollisionDetector2(Object *object1,Object *object2)
{
	if(object1 != object2)
	{
		double r1 = object1->get_radius();
		double r2 = object2->get_radius();
		Point distance;
		distance.x = object2->get_x() - object1->get_x();
		distance.y = object2->get_y() - object1->get_y();
		double d = VectorSize(distance);
		if(d <= r1+r2) return true;
		else return false;
	}
	else return false;
}

bool Game::Collision(Object *object1,Object *object2)
{
	bool collided = CollisionDetector(object1,object2);
	if(collided)
	{
		std::vector<Point> new_velocities = CalculateCollisionVelocity(object1,object2);
		object1->set_vx(new_velocities[0].x);
		object1->set_vy(new_velocities[0].y);
		object2->set_vx(new_velocities[1].x);
		object2->set_vy(new_velocities[1].y);
		object1->Move(0.02);
		object2->Move(0.02);
	}
	return collided;
}

std::vector<Point> Game::CalculateCollisionVelocity(Object *object1,Object *object2)
{
	std::vector<Point> new_velocities;
	Point v1(object1->get_vx(),object1->get_vy());
	Point x1(object1->get_x(),object1->get_y());
	Point v2(object2->get_vx(),object2->get_vy());
	Point x2(object2->get_x(),object2->get_y());
	Point x1_x2 = SubtractVector(x1,x2);
	Point x2_x1 = VectorMultiplication(-1,x1_x2);
	Point v1_v2 = SubtractVector(v1,v2);
	Point v2_v1 = VectorMultiplication(-1,v1_v2);
	int mass1 = object1->get_mass();
	int mass2 = object2->get_mass();
	int coeff  =(2*mass2)/(mass1+mass2)*((DotProduct(v1_v2,x1_x2))/pow(VectorSize(x1_x2),2));
	int coeff2 =(2*mass1)/(mass1+mass2)*((DotProduct(v2_v1,x2_x1))/pow(VectorSize(x2_x1),2));
	new_velocities.push_back(SubtractVector(v1,VectorMultiplication(coeff,x1_x2)));
	new_velocities.push_back(SubtractVector(v2,VectorMultiplication(coeff2,x2_x1)));
	return new_velocities;
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