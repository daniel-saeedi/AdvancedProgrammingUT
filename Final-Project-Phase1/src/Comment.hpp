#ifndef COMMENT_H
#define COMMENT_H
#include "User.hpp"
#include <iostream>
#include <string>
class Comment
{
public:
	Comment(User *_user,int _time,std::string _comment) 
		: user(_user),time(_time),comment(_comment) {};
	void print_info();
	int get_time(){return time;}
	std::string get_username(){return user->get_username();}
private:
	int time;
	std::string comment;
	User *user;
};
#endif