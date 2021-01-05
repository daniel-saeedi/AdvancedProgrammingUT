#ifndef ADD_SONG_HANDLER_H
#define ADD_SONG_HANDLER_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "../../../server/server.hpp"
#include "../../Utunes.hpp"
class AddSongHandler : public RequestHandler
{
public:
	AddSongHandler(Utunes* _utunes) : utunes(_utunes){}
	Response* callback(Request* request);
private:
	Utunes* utunes;
};
#endif