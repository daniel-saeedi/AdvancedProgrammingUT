#ifndef REMOVE_SONG_HANDLER_H
#define REMOVE_SONG_HANDLER_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "../../../server/server.hpp"
#include "../../Utunes.hpp"
class RemoveSongHandler : public RequestHandler
{
public:
	RemoveSongHandler(Utunes* _utunes) : utunes(_utunes){}
	Response* callback(Request* request);
private:
	Utunes* utunes;
};
#endif