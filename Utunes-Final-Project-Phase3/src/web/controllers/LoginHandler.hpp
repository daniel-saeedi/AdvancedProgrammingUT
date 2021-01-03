#ifndef LOGIN_HANDLER_H
#define LOGIN_HANDLER_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "../../../server/server.hpp"
#include "../../Utunes.hpp"
class LoginHandler : public RequestHandler
{
public:
	LoginHandler(Utunes* _utunes) : utunes(_utunes){}
	Response* callback(Request* request);
private:
	Utunes* utunes;
};
#endif