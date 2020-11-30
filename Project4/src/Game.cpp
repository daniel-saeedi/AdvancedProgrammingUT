#include "Game.hpp"
#include "Exception/PlayerNotJoinedException.hpp"


Game::Game()
{
	
}

void Game::add_unassgined_player(std::string name)
{
	unassigned_players.push_back(name);
}

void Game::create_player(std::string name,std::string role)
{
	
}

void Game::assign_role(std::string name,std::string role)
{
	if(unassigned_player_exists(name))
	{
		create_player(name,role);
	}
	else
	{
		throw PlayerNotJoinedException();
	}
}

bool Game::unassigned_player_exists(std::string name)
{
	for(int i = 0;i < unassigned_players.size();i++)
	{
		if(unassigned_players[i] == name) return true;
		break;
	}
	return false;
}