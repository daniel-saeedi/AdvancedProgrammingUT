#include "Comment.hpp"

void Comment::print_info()
{
	std::cout << time << " ";
	std::cout << user->get_username() << ": ";
	std::cout << comment << std::endl;
}