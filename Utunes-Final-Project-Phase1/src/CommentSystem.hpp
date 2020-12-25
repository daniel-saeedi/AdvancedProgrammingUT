#ifndef COMMENT_SYSTEM_H
#define COMMENT_SYSTEM_H
#include "Comment.hpp"
#include "User.hpp"
#include <vector>
class CommentSystem
{
public:
	void add_comment(User *_user,int _time,std::string _comment);
	void get_comments();
	int get_total_comments(){return comments.size();}
private:
	std::vector<Comment*> comments;
};
#endif