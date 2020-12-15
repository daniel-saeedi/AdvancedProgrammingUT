#include "Utunes.hpp"
#include "Playlist.hpp"
#include "Exception/BadRequestException.hpp"
#include "Exception/NotFoundException.hpp"
#include "Exception/EmptyException.hpp"
constexpr char ID[] = "id";
constexpr char EMPTY[] = "Empty";
constexpr char USERNAME[] = "username";
const int INVALID = -1;

Utunes::Utunes(vector<Song*> _songs) : songs(_songs)
{
	auth_sys = new AuthenticationSystem();
	playlist_sys = new PlaylistSystem;
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

void Utunes::check_login()
{
	auth_sys->is_logged_in();
}

void Utunes::get_users()
{
	if((users.size() - 1) <= 0) throw EmptyException();
	User *current_user = auth_sys->get_session()->get_user();
	for(int i = 0;i < users.size();i++)
	{
		if(current_user != users[i]) users[i]->print_username();
	}
}

void Utunes::add_playlist(vector<std::string> playlist_info)
{
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
	playlist_sys->new_playlist(name,private_status,user);
	print_ok();
}

void Utunes::add_song_to_playlist(vector<std::string> playlist_info)
{
	int playlist_id;
	int song_id;
	for(int i = 0;i < playlist_info.size();i++)
	{
		if(playlist_info[i] == "playlist_id") playlist_id = stoi(playlist_info[i+1]);
		else if(playlist_info[i] == "song_id") song_id = stoi(playlist_info[i+1]);
	}
	User *user = auth_sys->get_session()->get_user();
	Song* song = find_song_by_id(song_id);
	if(song)
	playlist_sys->add_song_to_playlist(playlist_id,song,user);
	print_ok();
}

void Utunes::delete_playlist_song(vector<std::string> playlist_info)
{
	int playlist_id;
	int song_id;
	for(int i = 0;i < playlist_info.size();i++)
	{
		if(playlist_info[i] == "playlist_id") playlist_id = stoi(playlist_info[i+1]);
		else if(playlist_info[i] == "song_id") song_id = stoi(playlist_info[i+1]);
	}
	User *user = auth_sys->get_session()->get_user();
	Song* song = find_song_by_id(song_id);
	playlist_sys->delete_song(playlist_id,song,user);
	print_ok();
}


void Utunes::get_playlists(vector<std::string> playlist_info)
{
	std::string username;
	for(int i = 0;i < playlist_info.size();i++)
	{
		if(playlist_info[i] == USERNAME) username = playlist_info[i+1];
	}
	if(!user_exists(username)) throw NotFoundException();
	User *current_user = auth_sys->get_session()->get_user();
	User *user = find_user(username);
	playlist_sys->show_playlist(user,current_user);
}

void Utunes::get_playlist_songs(vector<std::string> playlist_info)
{
	int playlist_id;
	for(int i = 0;i < playlist_info.size();i++)
	{
		if(playlist_info[i] == "playlist_id") playlist_id = stoi(playlist_info[i+1]);
	}
	User *current_user = auth_sys->get_session()->get_user();
	playlist_sys->show_playlist_songs(playlist_id,current_user);	
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

void Utunes::add_comment(vector<std::string> playlist_info)
{
	int song_id;
	int time;
	std::string comment;
	for(int i = 0;i < playlist_info.size();i++)
	{
		if(playlist_info[i] == "song_id") song_id = stoi(playlist_info[i+1]);
		else if(playlist_info[i] == "time") time = stoi(playlist_info[i+1]);
		else if(playlist_info[i] == "comment") comment = playlist_info[i+1];
	}
	if(!song_exists(song_id)) throw NotFoundException();
	User *user = auth_sys->get_session()->get_user();
	Song* song = find_song_by_id(song_id);
	song->add_comment(user,time,comment);
	print_ok();
}

void Utunes::get_comments(vector<std::string> playlist_info)
{
	int song_id;
	for(int i = 0;i < playlist_info.size();i++)
	{
		if(playlist_info[i] == "song_id") song_id = stoi(playlist_info[i+1]);
	}
	if(!song_exists(song_id)) throw NotFoundException();
	Song* song = find_song_by_id(song_id);
	song->get_comments();
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

bool Utunes::user_exists(std::string username)
{
	for(int i = 0;i < users.size();i++)
	{
		if(users[i]->is_username_equal(username)) return true;
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

User* Utunes::find_user(std::string username)
{
	User* user = nullptr;
	for(int i = 0;i < users.size();i++)
	{
		if(users[i]->is_username_equal(username)) user = users[i];
	}
	return user;
}

void Utunes::print_ok()
{
	std::cout << "OK" << std::endl;
}