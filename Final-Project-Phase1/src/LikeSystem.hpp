#ifndef LIKE_SYSTEM_H
#define LIKE_SYSTEM_H
#include <iostream>
#include <vector>
#include "Like.hpp"
#include "User.hpp"
class LikeSystem
{
public:
	void like(User *user);
	bool like_exists(User *user);
	void delete_like(User *user);
	int get_total_likes(){return likes.size();}
private:
	std::vector<Like*> likes;
	void new_like(User *user);
};
#endif