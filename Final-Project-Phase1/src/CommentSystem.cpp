#include "CommentSystem.hpp"
#include<algorithm>
#include <tuple>
bool compare_comments(Comment *comment1, Comment *comment2)
{
	if(comment1->get_time() == comment2->get_time())
		return comment1->get_username() < comment2->get_username();
	else 
		return comment1->get_time() < comment2->get_time();
}
void CommentSystem::add_comment(User *_user,int _time,std::string _comment)
{
	Comment *comment = new Comment(_user,_time,_comment);
	comments.push_back(comment);
}

void CommentSystem::get_comments()
{
	sort(comments.begin(),comments.end(),compare_comments);
	for(int i = 0;i < comments.size();i++)
	{
		comments[i]->print_info();
	}
}