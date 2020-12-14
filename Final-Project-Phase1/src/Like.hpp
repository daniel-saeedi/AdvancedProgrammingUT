#ifndef LIKE_H
#define LIKE_H
#include "User.hpp"
class Like
{
public:
	Like(User *_user) : user(_user){}
	bool is_equal(User *_user);
private:
	User *user;
};
#endif