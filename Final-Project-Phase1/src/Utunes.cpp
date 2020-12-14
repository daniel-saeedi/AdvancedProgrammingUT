#include "Utunes.hpp"
#include "Exception/BadRequestException.hpp"
#include "Exception/NotFoundException.hpp"
#include "Exception/EmptyException.hpp"
constexpr char ID[] = "id";
constexpr char EMPTY[] = "Empty";
const int INVALID = -1;

Utunes::Utunes(vector<Song*> _songs) : songs(_songs)
{
	auth_sys = new AuthenticationSystem();
}

void Utunes::signup(vector<std::string> signup_info)
{
	std::string email;
	std::string username;
	std::string password;
	for(int i = 0;i < signup_info.size();i++)
	{
		if(signup_info[i] == "email") email = signup_info[i+1];
		else if(signup_info[i] == "username") username = signup_info[i+1];
		else if(signup_info[i] == "password") password = signup_info[i+1];
	}
	create_new_user(email,username,password);
	auth_sys->login(users,email,password);
	print_ok();
}

void Utunes::create_new_user(std::string email,std::string username,std::string password)
{
	if(email_username_exists(email,username)) throw BadRequestException();
	User *new_user = new User(email,username,password);
	users.push_back(new_user);
}

bool Utunes::email_username_exists(std::string email,std::string username)
{
	for(int i = 0;i < users.size();i++)
	{
		if(users[i]->is_email_username_equal(email,username)) return true;
	}
	return false;
}

void Utunes::login(vector<std::string> login_info)
{
	std::string email;
	std::string password;
	for(int i = 0;i < login_info.size();i++)
	{
		if(login_info[i] == "email") email = login_info[i+1];
		else if(login_info[i] == "password") password = login_info[i+1];
	}
	auth_sys->login(users,email,password);
	print_ok();
}

void Utunes::logout()
{
	auth_sys->logout();
	print_ok();
}

void Utunes::add_playlist(vector<std::string> playlist_info)
{
	int id = 0;
	std::string name;
	bool private_status;
	for(int i = 0;i < playlist_info.size();i++)
	{
		if(playlist_info[i] == "name") name = playlist_info[i+1];
		else if(playlist_info[i] == "privacy")
		{
			if(playlist_info[i+1] == "private") private_status = true;
			if(playlist_info[i+1] == "public") private_status = false;
		}
	}
	User *user = auth_sys->get_session()->get_user();
	//user->add_playlist(id,name,private_status);
	print_ok();
}

void Utunes::get_songs()
{
	Session *current_session = auth_sys->get_session();
	if(songs.size() == 0 || current_session->is_songs_filtered()) throw EmptyException();
	if(current_session->is_songs_filtered()) current_session->show_songs();
	else show_songs();
}

void Utunes::get_song(vector<std::string> song_id)
{
	int id = extract_id(song_id);
	Song *song = find_song_by_id(id);
	song->print_single_info();
}

void Utunes::show_songs()
{
	for(int i = 0;i < songs.size();i++)
	{	
		songs[i]->print_info();
	}
}

void Utunes::new_like(vector<std::string> song_id)
{
	int id = extract_id(song_id);
	User *user = auth_sys->get_session()->get_user();
	Song *song = find_song_by_id(id);
	song->like(user);
	print_ok();
}

void Utunes::show_likes()
{
	std::vector<Song*> liked_songs = get_liked_songs();
	if(liked_songs.size() == 0) throw EmptyException();
	for(int i = 0;i < liked_songs.size();i++)
	{
		liked_songs[i]->print_info();
	}
}

void Utunes::delete_like(vector<std::string> song_id)
{
	int id = extract_id(song_id);
	User *user = auth_sys->get_session()->get_user();
	Song *song = find_song_by_id(id);
	song->delete_like(user);
	print_ok();
}

int Utunes::extract_id(vector<std::string> song_id)
{
	int id = INVALID;
	for(int i = 0;i < song_id.size();i++)
	{
		if(song_id[i] == ID) id = stoi(song_id[i+1]);
	}
	if(id == INVALID || !song_exists(id)) throw NotFoundException();
	return id;
}

std::vector<Song*> Utunes::get_liked_songs()
{
	std::vector<Song*> liked_songs;
	User *user = auth_sys->get_session()->get_user();
	for(int i = 0;i < songs.size(); i++)
	{
		if(songs[i]->has_liked(user)) liked_songs.push_back(songs[i]);
	}
	return liked_songs;
}

bool Utunes::song_exists(int id)
{
	for(int i = 0;i < songs.size();i++)
	{
		if(songs[i]->is_equal(id)) return true;
	}
	return false;
}

Song* Utunes::find_song_by_id(int id)
{
	Song* song = nullptr;
	for(int i = 0;i < songs.size();i++)
	{
		if(songs[i]->is_equal(id)) song = songs[i];
	}
	return song;
}

void Utunes::check_login()
{
	auth_sys->is_logged_in();
}

void Utunes::print_ok()
{
	std::cout << "OK" << std::endl;
}




