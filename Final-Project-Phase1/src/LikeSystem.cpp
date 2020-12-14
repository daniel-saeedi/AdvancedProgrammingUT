#include "LikeSystem.hpp"
#include "Exception/BadRequestException.hpp"

void LikeSystem::like(User *user)
{
	if(like_exists(user)) throw BadRequestException();
	new_like(user);
}

void LikeSystem::new_like(User *user)
{
	likes.push_back(new Like(user));
}

bool LikeSystem::like_exists(User *user)
{
	for(int i = 0;i < likes.size();i++)
	{
		if(likes[i]->is_equal(user)) return true;
	}
	return false;
}

void LikeSystem::delete_like(User *user)
{
	if(!like_exists(user)) throw BadRequestException();
	for(int i = 0;i < likes.size();i++)
	{
		Like* like = likes[i];
		if(like->is_equal(user))
		{
			delete like;
			likes.erase(likes.begin() + i);
			break;
		}
	}
}