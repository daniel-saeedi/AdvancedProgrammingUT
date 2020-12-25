#include "RecommendationSystem.hpp"
using namespace std;
constexpr int PRECISION = 2;

bool compare_number(std::pair<User*,double> a,std::pair<User*,double> b);
bool compare_songs_confidence(std::pair<Song*,double> a,std::pair<Song*,double> b);
double remove_digits(double n,int digits);

void RecommendationSystem::get_similar_users(int count,User *current_user,const std::vector<User*> &users,const std::vector<Song*> &songs)
{
	std::vector<std::pair<User*,double>> users_similarity = get_users_similarity(current_user,users,songs);
	print_similar_users(count,current_user,users_similarity);
}

std::vector<std::pair<User*,double>> RecommendationSystem::get_users_similarity(User *current_user,const std::vector<User*> &users,const std::vector<Song*> &songs)
{
	std::vector<std::vector<double>> similarity_matrix = get_similarity_matrix(users,songs);
	int current_user_index = find_user_index(users,current_user);
	std::vector<double> current_user_similarity = similarity_matrix[current_user_index];
	std::vector<std::pair<User*,double>> users_similarity = get_similar_users_pair(users,current_user_similarity);
	sort(users_similarity.begin(),users_similarity.end(),compare_number);
	return users_similarity;
}

void RecommendationSystem::get_recommendation(int count,User *current_user,const std::vector<User*> &users,const std::vector<Song*> &songs)
{
	std::vector<std::pair<Song*,double>> songs_confidence = get_songs_confidence(current_user,users,songs);
	print_recommendation(count,songs_confidence);
}

std::vector<std::pair<Song*,double>> RecommendationSystem::get_songs_confidence(User *current_user,const std::vector<User*> &users,const std::vector<Song*> &songs)
{
	std::vector<std::vector<double>> similarity_matrix = get_similarity_matrix(users,songs);
	std::vector<std::pair<Song*,double>> songs_confidence;
	for(int i = 0;i < songs.size();i++)
	{
		std::pair<Song*,double> pair;
		pair.first = songs[i];
		pair.second = calculate_confidence(songs[i],current_user,users,similarity_matrix);
		songs_confidence.push_back(pair);
	}
	sort(songs_confidence.begin(),songs_confidence.end(),compare_songs_confidence);
	return songs_confidence;
}

std::vector<std::vector<bool>> RecommendationSystem::get_songs_users_matrix(const std::vector<User*> &users,const std::vector<Song*> &songs)
{
	std::vector<std::vector<bool>> matrix;
	for(int i = 0;i < users.size();i++)
	{
		std::vector<bool> row;
		for(int j = 0;j < songs.size();j++)
		{
			row.push_back(songs[j]->has_liked(users[i]));
		}
		matrix.push_back(row);
	}
	return matrix;
}

std::vector<std::vector<double>> RecommendationSystem::get_similarity_matrix(const std::vector<User*> &users,const std::vector<Song*> &songs)
{
	std::vector<std::vector<double>> matrix;
	int count_users = users.size();
	for(int i = 0;i < users.size();i++)
	{
		std::vector<double> row;
		for(int j = 0;j < users.size();j++)
		{
			int total_same_likes = count_same_likes(users[i],users[j],songs);
			double similarity = calculate_similarity(total_same_likes,count_users);
			row.push_back(similarity);
		}
		matrix.push_back(row);
	}
	return matrix;
}

double RecommendationSystem::calculate_confidence(Song *song,User *user,const std::vector<User*> &users,std::vector<std::vector<double>> similarity_matrix)
{
	double score = 0;
	int other_users_count = users.size()-1;
	int user_index = find_user_index(users,user);
	for(int i = 0;i < users.size();i++)
	{
		double similarity = similarity_matrix[user_index][i];
		if(users[i] != user)
			score += song->has_liked(users[i]) * similarity;
	}
	return remove_digits((score/other_users_count)*100,PRECISION);
}

int RecommendationSystem::find_user_index(const std::vector<User*> &users,User *user)
{
	for(int i = 0;i < users.size();i++)
	{
		if(users[i] == user)return i;
	}
	return -1;
}

double RecommendationSystem::calculate_similarity(int total_same_likes,int total_users)
{
	return (double)total_same_likes / (double)total_users;
}

int RecommendationSystem::count_same_likes(User *user1,User *user2,const std::vector<Song*> &songs)
{
	int count = 0;
	for(int i = 0;i < songs.size();i++)
	{
		if(songs[i]->has_liked(user1) && songs[i]->has_liked(user2)) count++;
	}
	return count;
}

void RecommendationSystem::print_similar_users(int count,User *current_user,std::vector<std::pair<User*,double>> users_similarity)
{
	for(int i = 0;i < users_similarity.size();i++)
	{
		if(i > count) break;
		User *user = users_similarity[i].first;
		if(current_user != user)
		{
			std::cout << std::fixed << std::showpoint;
			std::cout << std::setprecision(2);
			std::cout << users_similarity[i].second << "% ";
			std::cout << user->get_username() << std::endl;
		}
	}
}

void RecommendationSystem::print_recommendation(int count,std::vector<std::pair<Song*,double>> songs_confidence)
{
	for(int i = 0;i < songs_confidence.size();i++)
	{
		if(i >= count) break;
		Song *song = songs_confidence[i].first;
		double song_confidence = songs_confidence[i].second;
		song->print_info(song_confidence);
	}
}

std::vector<std::pair<User*,double>> RecommendationSystem::get_similar_users_pair(const std::vector<User*> &users,std::vector<double> similarity_matrix)
{
	std::vector<pair<User*,double>> vec;
	for(int i = 0;i < users.size();i++)
	{
		pair<User*,double> p;
		p.first = users[i];
		p.second = similarity_matrix[i];
		vec.push_back(p);
	}
	return vec;
}

bool compare_number(std::pair<User*,double> a,std::pair<User*,double> b)
{
	return a.second > b.second;
}

double remove_digits(double n,int digits)
{
	return std::floor(n * (double)pow(10,digits)) / pow(10,digits);
}

bool compare_songs_confidence(std::pair<Song*,double> a,std::pair<Song*,double> b)
{
	if(a.second == b.second)
	{
		Song *song1 = a.first;
		Song *song2 = b.first;
		return song1->get_id() < song2->get_id();
	}
	else
		return a.second > b.second;
}







