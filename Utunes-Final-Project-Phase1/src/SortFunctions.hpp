#ifndef SORT_FUNCTIONS_H
#define SORT_FUNCTIONS_H
#include "Song.hpp"
#include "User.hpp"
bool compare_by_id(Song *song1,Song *song2)
{
	return song1->get_id() < song2->get_id();
}

bool compare_by_username(User *user1,User *user2)
{
	return user1->get_username() < user2->get_username();
}
#endif