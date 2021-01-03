#ifndef RECOMMENDATION_SYSTEM_H
#define RECOMMENDATION_SYSTEM_H
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include "Song.hpp"
#include "User.hpp"
class RecommendationSystem
{
public:
	void get_similar_users(int count,User *current_user,const std::vector<User*> &users,const std::vector<Song*> &songs);
	void get_recommendation(int count,User *current_user,const std::vector<User*> &users,const std::vector<Song*> &songs);
	std::vector<Song*> get_recommended_songs(User *current_user,const std::vector<User*> &users,const std::vector<Song*> &songs);
private:
	std::vector<std::vector<bool>> get_songs_users_matrix(const std::vector<User*> &users,const std::vector<Song*> &songs);
	std::vector<std::vector<double>> get_similarity_matrix(const std::vector<User*> &users,const std::vector<Song*> &songs);
	double calculate_similarity(int total_same_likes,int total_users);
	int count_same_likes(User *user1,User *user2,const std::vector<Song*> &songs);
	double calculate_confidence(Song *song,User *user,const std::vector<User*> &users,std::vector<std::vector<double>> similarity_matrix);
	int find_user_index(const std::vector<User*> &users,User *user);
	std::vector<std::pair<User*,double>> get_similar_users_pair(const std::vector<User*> &users,std::vector<double> similarity_matrix);
	void print_similar_users(int count,User *current_user,std::vector<std::pair<User*,double>> users_similarity);
	void print_recommendation(User *current_user,int count,std::vector<std::pair<Song*,double>> songs_confidence);
	std::vector<std::pair<Song*,double>> get_songs_confidence(User *current_user,const std::vector<User*> &users,const std::vector<Song*> &songs);
	std::vector<std::pair<User*,double>> get_users_similarity(User *current_user,const std::vector<User*> &users,const std::vector<Song*> &songs);
};
#endif