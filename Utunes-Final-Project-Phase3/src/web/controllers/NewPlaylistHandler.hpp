#ifndef NEW_PLAYLISR_HANDLER_H
#define NEW_PLAYLISR_HANDLER_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "../../../server/server.hpp"
#include "../../Utunes.hpp"
class NewPlaylistHandler : public RequestHandler
{
public:
	NewPlaylistHandler(Utunes* _utunes) : utunes(_utunes){}
	Response* callback(Request* request);
private:
	Utunes* utunes;
};
#endif