#include "Game.hpp"
#include "Joker.hpp"
#include "Mafia.hpp"
#include "Villager.hpp"
#include "Silencer.hpp"
#include "Bulletproof.hpp"
#include "Detective.hpp"
#include "Doctor.hpp"
#include "Godfather.hpp"
#include "Exception/PlayerNotJoinedException.hpp"
#include "Exception/NotAllAssignedException.hpp"
#include "Exception/GameAlreadyStartedException.hpp"
constexpr char SILENCER[] = "silencer";
constexpr char BULLETPROOF[] = "bulletproof";
constexpr char DETECTIVE[] = "detective";
constexpr char DOCTOR[] = "doctor";
constexpr char GODFATHER[] = "godfather";
constexpr char JOKER[] = "joker";
constexpr char MAFIA[] = "mafia";
constexpr char VILLAGER[] = "villager";
constexpr char GET_STARTED[] = "Ready? Set! Go.";

Game::Game()
{
	start = false;
}

void Game::start_game()
{
	if(unassigned_players.size() > 0) throw NotAllAssignedException();
	else if(start) throw GameAlreadyStartedException();
	else
	{
		start = true;
		show_all_players();
		std::cout << GET_STARTED << std::endl;
	}
}

void Game::show_all_players()
{
	for(int i = 0;i < players.size();i++)
	{
		std::cout << players[i]->get_name() << ": " << players[i]->get_role() << std::endl;
	}
}

void Game::add_unassgined_player(std::string name)
{
	unassigned_players.push_back(name);
}

void Game::create_player(std::string name,std::string role)
{
	if(role == SILENCER) players.push_back(new Silencer(name));
	else if(role == BULLETPROOF) players.push_back(new Bulletproof(name));
	else if(role == DETECTIVE) players.push_back(new Detective(name));
	else if(role == DOCTOR) players.push_back(new Doctor(name));
	else if(role == GODFATHER) players.push_back(new Godfather(name));
	else if(role == JOKER) players.push_back(new Joker(name));
	else if(role == MAFIA) players.push_back(new Mafia(name));
	else if(role == VILLAGER) players.push_back(new Villager(name));
	//else throw illigal role.
}

void Game::update_player(int index,std::string role)
{
	std::string name = players[index]->get_name();
	if(role == SILENCER) players[index] = (new Silencer(name));
	else if(role == BULLETPROOF) players[index] = (new Bulletproof(name));
	else if(role == DETECTIVE) players[index] = (new Detective(name));
	else if(role == DOCTOR) players[index] = (new Doctor(name));
	else if(role == GODFATHER) players[index] = (new Godfather(name));
	else if(role == JOKER) players[index] = (new Joker(name));
	else if(role == MAFIA) players[index] = (new Mafia(name));
	else if(role == VILLAGER) players[index] = (new Villager(name));
	//else throw illigal role.
}

void Game::assign_role(std::string name,std::string role)
{
	if(player_exists(name))
	{
		int index = player_index(name);
		update_player(index,role);
	}
	else if(unassigned_player_exists(name))
	{
		create_player(name,role);
		int index = unassigned_player_index(name);
		unassigned_players.erase(unassigned_players.begin() + index);
	}
	else throw PlayerNotJoinedException();
}

bool Game::unassigned_player_exists(std::string name)
{
	for(int i = 0;i < unassigned_players.size();i++)
	{
		if(unassigned_players[i] == name) return true;
	}
	return false;
}

int Game::unassigned_player_index(std::string name)
{
	for(int i = 0;i < unassigned_players.size();i++)
	{
		if(unassigned_players[i] == name) return i;
	}
}

bool Game::player_exists(std::string name)
{
	for(int i = 0;i < players.size();i++)
	{
		if(players[i]->get_name() == name) return true;
	}
	return false;
}

int Game::player_index(std::string name)
{
	for(int i = 0;i < players.size();i++)
	{
		if(players[i]->get_name() == name) return i;
	}
}








