#include "CommentSystem.hpp"
void CommentSystem::add_comment(User *_user,int _time,std::string _comment)
{
	Comment *comment = new Comment(_user,_time,_comment);
	comments.push_back(comment);
}

void CommentSystem::get_comments()
{
	for(int i = 0;i < comments.size();i++)
	{
		comments[i]->print_info();
	}
}