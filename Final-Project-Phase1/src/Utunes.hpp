#ifndef UTUNES_H
#define UTUNES_H
#include "AuthenticationSystem.hpp"
#include "Song.hpp"
#include "User.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Utunes
{
public:
	Utunes(vector <Song*> _songs);
private:
	vector<Song*> songs;
	vector<User*> users;
};
#endif