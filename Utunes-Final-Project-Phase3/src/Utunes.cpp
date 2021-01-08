#include <algorithm>
#include "Utunes.hpp"
#include "Playlist.hpp"
#include "RecommendationSystem.hpp"
#include "SortFunctions.hpp"
#include "XOREncryption.hpp"
#include "Exception/BadRequestException.hpp"
#include "Exception/NotFoundException.hpp"
#include "Exception/EmptyException.hpp"
constexpr char PLAYLIST_MARK[] = "#playlists: ";
constexpr char OK[] = "OK";
const int INVALID = -1;

Utunes::Utunes(vector<Song*> _songs) : songs(_songs)
{
	sort(songs.begin(),songs.end(),compare_by_id);
	auth_sys = new AuthenticationSystem();
	playlist_sys = new PlaylistSystem;
	recommendation_sys = new RecommendationSystem;
}

Utunes::~Utunes()
{
	delete auth_sys;
	delete playlist_sys;
	for(int i = 0;i < songs.size();i++)
		delete songs[i];
	for(int i = 0;i < users.size();i++)
		delete users[i];
}

void Utunes::signup(std::string email,std::string username,std::string password,bool printok)
{
	create_new_user(email,username,password);
	login(email,password);
	if(printok) print_ok();
}

void Utunes::login(std::string email,std::string password)
{
	//Encrypting the password
	password = XOREncryption::encrypt_decrypt(password);
	auth_sys->login(users,email,password);
	print_ok();
}

bool Utunes::users_exists(std::string email,std::string password)
{
	password = XOREncryption::encrypt_decrypt(password);
	return auth_sys->check_login(users,email,password);
}

void Utunes::create_new_user(std::string email,std::string username,std::string password)
{
	//Encrypting the password
	password = XOREncryption::encrypt_decrypt(password);
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

void Utunes::logout(bool printok)
{
	auth_sys->logout();
	if(printok) print_ok();
}

void Utunes::check_login()
{
	//auth_sys->is_logged_in();
}

void Utunes::get_users()
{
	check_login();
	if((users.size() - 1) <= 0) throw EmptyException();
	User *current_user = auth_sys->get_session()->get_user();
	sort(users.begin(),users.end(),compare_by_username);
	for(int i = 0;i < users.size();i++)
	{
		if(current_user != users[i]) users[i]->print_username();
	}
}

void Utunes::get_similar_users(int count)
{
	check_login();
	User *current_user = auth_sys->get_session()->get_user();
	recommendation_sys->get_similar_users(count,current_user,users,songs);
}

void Utunes::get_recommendation(int count)
{
	check_login();
	User *current_user = auth_sys->get_session()->get_user();
	recommendation_sys->get_recommendation(count,current_user,users,songs);
}

std::vector<Song*> Utunes::get_recommended_songs(User* current_user)
{
	return recommendation_sys->get_recommended_songs(current_user,users,songs);
}

void Utunes::delete_filters()
{
	check_login();
	Session *session = auth_sys->get_session();
	session->delete_filters();
	print_ok();
}

std::vector<Song*> Utunes::get_filtered_songs()
{
	check_login();
	Session *session = auth_sys->get_session();
	return session->get_filtered_songs(songs);
}

void Utunes::add_artist_filter(std::string artist)
{
	check_login();
	Session *session = auth_sys->get_session();
	session->add_artist_filter(artist);
	print_ok();
}

void Utunes::add_publish_year_filter(int min_year,int max_year)
{
	check_login();
	Session *session = auth_sys->get_session();
	session->add_public_year_filter(min_year,max_year);
	print_ok();
}

void Utunes::add_likes_filter(int min_like,int max_like)
{
	check_login();
	Session *session = auth_sys->get_session();
	session->add_likes_filter(min_like,max_like);
	print_ok();
}

void Utunes::add_playlist(std::string name,bool private_status,User* user)
{
	check_login();
	if(user == nullptr)
		user = auth_sys->get_session()->get_user();
	playlist_sys->new_playlist(name,private_status,user);
}

void Utunes::add_song_to_playlist(int playlist_id,int song_id)
{
	check_login();
	User *user = auth_sys->get_session()->get_user();
	Song* song = find_song_by_id(song_id);
	if(song != nullptr)
		playlist_sys->add_song_to_playlist(playlist_id,song,user);
	print_ok();
}

void Utunes::delete_playlist_song(int playlist_id,int song_id)
{
	check_login();
	User *user = auth_sys->get_session()->get_user();
	Song* song = find_song_by_id(song_id);
	playlist_sys->delete_song(playlist_id,song,user);
	print_ok();
}

void Utunes::get_playlists(std::string username)
{
	check_login();
	if(!user_exists(username)) throw NotFoundException();
	User *current_user = auth_sys->get_session()->get_user();
	User *user = find_user(username);
	playlist_sys->show_playlist(user,current_user);
}

void Utunes::get_playlist_songs(int playlist_id)
{
	check_login();
	User *current_user = auth_sys->get_session()->get_user();
	playlist_sys->show_playlist_songs(playlist_id,current_user);	
}

void Utunes::get_songs()
{
	check_login();
	Session *current_session = auth_sys->get_session();
	if(songs.size() == 0) throw EmptyException();
	if(current_session->is_songs_filtered()) current_session->show_songs(songs);
	else show_songs();
}

void Utunes::get_song(int id)
{
	check_login();
	if(!song_exists(id)) throw NotFoundException();
	Song *song = find_song_by_id(id);
	song->print_single_info();
	int num_of_playlists = playlist_sys->count_playlists_contain_song(song);
	std::cout << PLAYLIST_MARK << num_of_playlists << std::endl;
}

void Utunes::show_songs()
{
	check_login();
	for(int i = 0;i < songs.size();i++)
	{	
		songs[i]->print_info();
	}
}

void Utunes::new_like(int id,User *user)
{
	check_login();
	if(!song_exists(id)) throw NotFoundException();
	if(user == nullptr)
		user = auth_sys->get_session()->get_user();
	Song *song = find_song_by_id(id);
	song->like(user);
}

void Utunes::show_likes()
{
	check_login();
	std::vector<Song*> liked_songs = get_liked_songs();
	sort(liked_songs.begin(),liked_songs.end(),compare_by_id);
	if(liked_songs.size() == 0) throw EmptyException();
	for(int i = 0;i < liked_songs.size();i++)
	{
		liked_songs[i]->print_info();
	}
}

void Utunes::delete_like(int id,User* user)
{
	check_login();
	if(!song_exists(id)) throw NotFoundException();
	if(user == nullptr)
		user = auth_sys->get_session()->get_user();
	Song *song = find_song_by_id(id);
	song->delete_like(user);
	print_ok();
}

void Utunes::add_comment(int song_id,int time,std::string comment)
{
	check_login();
	if(!song_exists(song_id)) throw NotFoundException();
	User *user = auth_sys->get_session()->get_user();
	Song* song = find_song_by_id(song_id);
	song->add_comment(user,time,comment);
	print_ok();
}

void Utunes::get_comments(int song_id)
{
	check_login();
	if(!song_exists(song_id)) throw NotFoundException();
	Song* song = find_song_by_id(song_id);
	song->get_comments();
}

std::vector<Song*> Utunes::get_liked_songs(User *user)
{
	std::vector<Song*> liked_songs;
	if(user == nullptr)
		user = auth_sys->get_session()->get_user();
	for(int i = 0;i < songs.size(); i++)
	{
		if(songs[i]->has_liked(user)) liked_songs.push_back(songs[i]);
	}
	sort(liked_songs.begin(),liked_songs.end(),compare_by_id);
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

User* Utunes::find_user_by_email(std::string email)
{
	User* user = nullptr;
	for(int i = 0;i < users.size();i++)
	{
		if(users[i]->is_email_equal(email)) user = users[i];
	}
	return user;
}

void Utunes::print_ok()
{
	//std::cout << OK << std::endl;
}