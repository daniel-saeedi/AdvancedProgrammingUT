#ifndef COMMENT_H
#define COMMENT_H
#include "User.hpp"
class Comment
{
public:
	Comment(User *_user,int _time,std::string _comment) 
		: user(_user), time(_time), comment(_comment) {};
	void print_info();
private:
	int time;
	std::string comment;
	User *user;
};
#endif