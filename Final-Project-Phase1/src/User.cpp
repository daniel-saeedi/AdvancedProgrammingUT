#include "User.hpp"

bool User::is_email_username_equal(std::string _email,std::string _username)
{
	if(email == _email || username == _username) return true;
	return false;
}

bool User::check_email_password(std::string _email,std::string _password)
{
	if(email == _email && password == _password) return true;
	return false;
}

// bool User::add_playlist(int id,std::string name,bool private_status)
// {
// 	Playlist* playlist = new Playlist(id,name,private_status);
// 	playlists.push_back(playlist);
// }