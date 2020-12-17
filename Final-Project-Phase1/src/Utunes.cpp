#include <algorithm>
#include "Utunes.hpp"
#include "Playlist.hpp"
#include "SortFunctions.hpp"
#include "XOREncryption.hpp"
#include "Exception/BadRequestException.hpp"
#include "Exception/NotFoundException.hpp"
#include "Exception/EmptyException.hpp"
constexpr char ID[] = "id";
constexpr char EMAIL[] = "email";
constexpr char USERNAME[] = "username";
constexpr char PASSWORD[] = "password";
constexpr char MIN_YEAR[] = "min_year";
constexpr char MAX_YEAR[] = "max_year";
constexpr char MIN_LIKE[] = "min_like";
constexpr char MAX_LIKE[] = "max_like";
constexpr char ARTIST[] = "artist";
constexpr char PRIVATE[] = "private";
constexpr char PUBLIC[] = "public";
constexpr char NAME[] = "name";
constexpr char PRIVACY[] = "privacy";
constexpr char PLAYLIST_ID[] = "playlist_id";
constexpr char SONG_ID[] = "song_id";
constexpr char PLAYLIST_MARK[] = "#playlists: ";
constexpr char TIME[] = "time";
constexpr char COMMENT[] = "comment";
constexpr char OK[] = "OK";
const int INVALID = -1;

Utunes::Utunes(vector<Song*> _songs) : songs(_songs)
{
	sort(songs.begin(),songs.end(),compare_by_id);
	auth_sys = new AuthenticationSystem();
	playlist_sys = new PlaylistSystem;
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

void Utunes::signup(vector<std::string> signup_info)
{
	std::map<std::string,std::string> data = split({EMAIL, USERNAME, PASSWORD},signup_info);
	std::string email = data[EMAIL];
	std::string username = data[USERNAME];
	std::string password = data[PASSWORD];
	//Encrypting the password
	password = XOREncryption::encrypt_decrypt(password);
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
	std::map<std::string,std::string> data = split({EMAIL, PASSWORD},login_info);
	std::string email = data[EMAIL];
	std::string password = data[PASSWORD];
	//Encrypting the password
	password = XOREncryption::encrypt_decrypt(password);
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
	sort(users.begin(),users.end(),compare_by_username);
	for(int i = 0;i < users.size();i++)
	{
		if(current_user != users[i]) users[i]->print_username();
	}
}

void Utunes::add_filter(vector<std::string> filter_info)
{
	std::string operation = filter_info[0];
	if(operation == ARTIST) add_artist_filter(filter_info);
	else if(operation == MIN_YEAR) add_publish_year_filter(filter_info);
	else if(operation == MIN_LIKE) add_likes_filter(filter_info);
	else throw BadRequestException();
	print_ok();
}

void Utunes::delete_filters()
{
	Session *session = auth_sys->get_session();
	session->delete_filters();
	print_ok();
}

void Utunes::add_artist_filter(vector<std::string> filter_info)
{
	Session *session = auth_sys->get_session();
	std::string artist;
	int name_index = INVALID;
	for(int i = 0;i < filter_info.size();i++)
	{
		if(name_index != INVALID)
		{
			artist += filter_info[i];
			if(i < filter_info.size() - 1) artist += " ";
		}
		if(filter_info[i] == ARTIST) name_index = i + 1;
	}
	session->add_artist_filter(artist);
}

void Utunes::add_publish_year_filter(vector<std::string> filter_info)
{
	Session *session = auth_sys->get_session();
	std::map<std::string,std::string> data = split({MIN_YEAR, MAX_YEAR},filter_info);
	int min_year = stoi(data[MIN_YEAR]);
	int max_year = stoi(data[MAX_YEAR]);
	session->add_public_year_filter(min_year,max_year);
}

void Utunes::add_likes_filter(vector<std::string> filter_info)
{
	Session *session = auth_sys->get_session();
	std::map<std::string,std::string> data = split({MIN_LIKE, MAX_LIKE},filter_info);
	int min_like = stoi(data[MIN_LIKE]);
	int max_like = stoi(data[MAX_LIKE]);
	session->add_likes_filter(min_like,max_like);
}

void Utunes::add_playlist(vector<std::string> playlist_info)
{
	std::map<std::string,std::string> data = split({NAME, PRIVACY},playlist_info);
	std::string name = data[NAME];
	bool private_status;
	if(data[PRIVACY] == PRIVATE) private_status = true;
	if(data[PRIVACY] == PUBLIC) private_status = false;
	User *user = auth_sys->get_session()->get_user();
	playlist_sys->new_playlist(name,private_status,user);
}

void Utunes::add_song_to_playlist(vector<std::string> playlist_info)
{
	std::map<std::string,std::string> data = split({PLAYLIST_ID, SONG_ID},playlist_info);
	int playlist_id = stoi(data[PLAYLIST_ID]);
	int song_id = stoi(data[SONG_ID]);
	User *user = auth_sys->get_session()->get_user();
	Song* song = find_song_by_id(song_id);
	if(song != nullptr)
		playlist_sys->add_song_to_playlist(playlist_id,song,user);
	print_ok();
}

void Utunes::delete_playlist_song(vector<std::string> playlist_info)
{
	std::map<std::string,std::string> data = split({PLAYLIST_ID, SONG_ID},playlist_info);
	int playlist_id = stoi(data[PLAYLIST_ID]);
	int song_id = stoi(data[SONG_ID]);
	User *user = auth_sys->get_session()->get_user();
	Song* song = find_song_by_id(song_id);
	playlist_sys->delete_song(playlist_id,song,user);
	print_ok();
}

void Utunes::get_playlists(vector<std::string> playlist_info)
{
	std::map<std::string,std::string> data = split({USERNAME},playlist_info);
	std::string username = data[USERNAME];
	if(!user_exists(username)) throw NotFoundException();
	User *current_user = auth_sys->get_session()->get_user();
	User *user = find_user(username);
	playlist_sys->show_playlist(user,current_user);
}

void Utunes::get_playlist_songs(vector<std::string> playlist_info)
{
	std::map<std::string,std::string> data = split({PLAYLIST_ID},playlist_info);
	int playlist_id = stoi(data[PLAYLIST_ID]);
	User *current_user = auth_sys->get_session()->get_user();
	playlist_sys->show_playlist_songs(playlist_id,current_user);	
}

void Utunes::get_songs()
{
	Session *current_session = auth_sys->get_session();
	if(songs.size() == 0) throw EmptyException();
	if(current_session->is_songs_filtered()) current_session->show_songs(songs);
	else show_songs();
}

void Utunes::get_song(vector<std::string> song_id)
{
	int id = extract_id(song_id);
	Song *song = find_song_by_id(id);
	song->print_single_info();
	int num_of_playlists = playlist_sys->count_playlists_contain_song(song);
	std::cout << PLAYLIST_MARK << num_of_playlists << std::endl;
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
	sort(liked_songs.begin(),liked_songs.end(),compare_by_id);
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
	std::map<std::string,std::string> data = split({SONG_ID,TIME,COMMENT},playlist_info);
	int song_id = stoi(data[SONG_ID]);
	int time = stoi(data[TIME]);
	std::string comment = data[COMMENT];
	if(!song_exists(song_id)) throw NotFoundException();
	User *user = auth_sys->get_session()->get_user();
	Song* song = find_song_by_id(song_id);
	song->add_comment(user,time,comment);
	print_ok();
}

void Utunes::get_comments(vector<std::string> playlist_info)
{
	std::map<std::string,std::string> data = split({SONG_ID},playlist_info);
	int song_id = stoi(data[SONG_ID]);
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

std::map<std::string,std::string> Utunes::split(vector<std::string> headers,vector<std::string> info)
{
	std::map<std::string,std::string> result;
	for(int i = 0;i < headers.size();i++)
	{
		for(int j = 0;j < info.size();j++)
		{
			if(headers[i] == info[j]) result[headers[i]] = info[j+1];
		}
	}
	if(result.size() != headers.size()) throw BadRequestException();
	return result;
}

void Utunes::print_ok()
{
	std::cout << OK << std::endl;
}