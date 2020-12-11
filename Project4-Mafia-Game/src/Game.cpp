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
#include "Exception/SilencedException.hpp"
#include "Exception/NotAliveVoteeException.hpp"
#include "Exception/UserNotAliveException.hpp"
#include "Exception/UserCannotWakeupException.hpp"
#include "Exception/VotingInProgressException.hpp"
#include "Exception/CannotSwapException.hpp"
#include "Exception/CharactersAlreadySwappedException.hpp"
constexpr char SILENCER[] = "silencer";
constexpr char BULLETPROOF[] = "bulletproof";
constexpr char DETECTIVE[] = "detective";
constexpr char DOCTOR[] = "doctor";
constexpr char GODFATHER[] = "godfather";
constexpr char JOKER[] = "joker";
constexpr char MAFIA[] = "mafia";
constexpr char VILLAGER[] = "villager";
constexpr char GET_STARTED[] = "Ready? Set! Go.";
constexpr char MAFIA_KILL[] = "Mafia tried to kill ";
constexpr char JOKER_WON[] = "Joker won";
constexpr char VILLAGERS_WON[] = "Villagers won";
constexpr char MAFIA_WON[] = "Mafia won";
const int MAFIA_INDEX = 0;
const int VILLAGER_INDEX = 1;

bool compare_by_word(Player *player1,Player *player2)
{
    return player1->get_name() < player2->get_name();
}

Game::Game()
{
	start = false;
	voting_in_progress = false;
	finished = false;
	is_night = false;
	already_asked_to_swap = false;
	killed_player = nullptr;
	day_number = 0;
	day_vote_system = new VoteSystem();
	mafia_vote_system = new VoteSystem();
}

void Game::reset()
{
	for(int i = 0;i < players.size();i++)
	{
		players[i]->reset();
	}
}

void Game::end_night()
{
	is_night = false;
	Player* elected_player = mafia_vote_system->get_elected_player();
	if(elected_player != nullptr)
	{
		elected_player->kill();
		std::cout << MAFIA_KILL << elected_player->get_name() << std::endl;
		if(!elected_player->get_is_alive()) killed_player = elected_player;
	}
	mafia_vote_system->clear();
	reset();
	check_game_status();
	if(!finished) next_day();
}

void Game::night_events(std::string _voter,std::string _votee)
{
	if(!player_exists(_voter) || !player_exists(_votee)) throw PlayerNotJoinedException();
	Player *voter = players[player_index(_voter)];
	if(!voter->get_is_alive()) throw UserNotAliveException();
	if(!voter->can_wakeup()) throw UserCannotWakeupException();
	Player *candidate_to_kill = voter->vote_at_night(players[player_index(_votee)]);
	mafia_vote_to_kill(voter,candidate_to_kill);
}

void Game::mafia_vote_to_kill(Player* voter,Player *votee)
{
	if(votee != nullptr)
	{
		if(!votee->get_is_alive()) throw NotAliveVoteeException();
		mafia_vote_system->new_vote(voter,votee);
	}
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
		next_day();
	}
}

void Game::end_vote()
{
	voting_in_progress = false;
	already_asked_to_swap = false;
	Player* elected_player = day_vote_system->get_elected_player();
	if(elected_player != nullptr)
	{
		elected_player->kill();
		std::cout << elected_player->get_name() << " died" << std::endl;
		if(elected_player->is_joker())
		{
			finished = true;
			std::cout << JOKER_WON;
		}
	}
	day_vote_system->clear();
	check_game_status();
	if(!finished) start_night();
}

void Game::get_game_state()
{
	std::vector<int> count = count_players();
	int mafia_count = count[MAFIA_INDEX];
	int villager_count = count[VILLAGER_INDEX];
	std::cout << "Mafia = " << mafia_count << std::endl;
	std::cout << "Villager = " << villager_count << std::endl;
}

void Game::reset_silence()
{
	for(int i = 0;i < players.size();i++)
		players[i]->silence(false);
}

void Game::start_night()
{
	reset_silence();
	killed_player = nullptr;
	is_night = true;
	std::cout << "Night " << day_number << std::endl;
	show_wakeup_users();
}

void Game::check_game_status()
{
	if(start && !finished)
	{
		std::vector<int> count = count_players();
		int mafia_count = count[MAFIA_INDEX];
		int villager_count = count[VILLAGER_INDEX];
		if(mafia_count == 0)
		{
			finished = true;
			std::cout << VILLAGERS_WON;
		}
		else if(mafia_count >= villager_count)
		{
			finished = true;
			std::cout << MAFIA_WON;
		}
	}
}

std::vector<int> Game::count_players()
{
	int mafia_count = 0;
	int villager_count = 0;
	for(int i = 0;i < players.size();i++)
	{
		Player *player = players[i];
		if(player->get_is_alive())
		{
			if(player->is_mafia()) mafia_count++;
			if(player->is_villager()) villager_count++;
		}
	}
	std::vector<int> count;
	count.push_back(mafia_count);
	count.push_back(villager_count);
	return count;
}

void Game::show_wakeup_users()
{
	for(int i = 0;i < players.size();i++)
	{
		Player *player = players[i];
		if(player->can_wakeup() && player->get_is_alive()) 
			std::cout << player->get_name() << ": " << player->get_role() << std::endl;
	}
}

void Game::vote(std::string _voter,std::string _votee)
{
	if(!player_exists(_voter) || !player_exists(_votee)) throw PlayerNotJoinedException();
	Player *voter = players[player_index(_voter)];
	Player *votee = players[player_index(_votee)];
	if(voter->get_is_silenced()) throw SilencedException();
	if(!votee->get_is_alive()) throw NotAliveVoteeException();
	day_vote_system->new_vote(voter,votee);
	voting_in_progress = true;
}

void Game::next_day()
{
	day_number++;
	std::cout << "Day " << day_number << std::endl;
	show_killed_player();
	show_silenced_player();
	killed_player = nullptr;
}

void Game::show_killed_player()
{
	if(killed_player != nullptr)
		std::cout << killed_player->get_name() << " was killed" << std::endl;
}

void Game::show_silenced_player()
{
	std::vector<Player*> silenced = get_silenced_player();
	if(silenced.size() > 0)
	{
		std::string silenced_msg = "Silenced";
		for(int i = 0;i < silenced.size();i++)
		{
			silenced_msg += " " + silenced[i]->get_name();
		}
		std::cout << silenced_msg << std::endl;
	}
}

std::vector<Player*> Game::get_silenced_player()
{
	std::vector<Player*> silenced;
	for(int i = 0;i < players.size();i++)
	{
		if(players[i]->get_is_silenced()) silenced.push_back(players[i]);
	}
	sort(silenced.begin(),silenced.end(),compare_by_word);
	return silenced;
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

void Game::swap_character(std::string name1,std::string name2)
{
	if(!player_exists(name1) || !player_exists(name2)) throw PlayerNotJoinedException();
	Player *player1 = players[player_index(name1)];
	Player *player2 = players[player_index(name2)];
	if(!player1->get_is_alive() || !player2->get_is_alive()) throw UserNotAliveException();
	if(already_asked_to_swap) throw CharactersAlreadySwappedException();
	if(voting_in_progress) throw VotingInProgressException();
	if(is_night) throw CannotSwapException();
	swap_players(player1,player2);
	already_asked_to_swap = true;
}

void Game::swap_players(Player *player1,Player *player2)
{
	std::string player1_name = player1->get_name();
	std::string player2_name = player2->get_name();
	bool silence_state_player1 = player1->get_is_silenced();
	bool silence_state_player2 = player2->get_is_silenced();
	int player1_index = player_index(player1_name);
	int player2_index = player_index(player2_name);
	player1->change_name(player2_name);
	player1->silence(silence_state_player2);
	player2->change_name(player1_name);
	player2->silence(silence_state_player1);
	players[player1_index] = player2;
	players[player2_index] = player1;
}