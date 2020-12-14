#include "Like.hpp"

bool Like::is_equal(User *_user)
{
	if(user == _user) return true;
	return false;
}