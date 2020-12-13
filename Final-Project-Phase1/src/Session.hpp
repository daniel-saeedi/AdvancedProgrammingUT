#ifndef SESSION_H
#define SESSION_H
#include "User.hpp"
class Session
{
public:
	Session(User *_user);
private:
	User *user;
};
#endif