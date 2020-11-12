#include "Player.hpp"
#define TEAM_A 1
#define TEAM_B 2

//Constructor
Player::Player(int _position_x,int _position_y,int _team_id)
{
	if(_team_id == TEAM_A) player_image = "Assets/Player1.png";
	if(_team_id == TEAM_B) player_image = "Assets/Player2.png";
	position_x = _position_x;
	position_y = _position_y;
	team_id = _team_id;
	width = 80;
	height = 80;
}