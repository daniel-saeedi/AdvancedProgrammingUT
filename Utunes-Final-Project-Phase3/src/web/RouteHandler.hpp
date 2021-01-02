#ifndef ROUTE_HANDLER_H
#define ROUTE_HANDLER_H
#include <iostream>
#include <vector>
#include <string>
#include "../Utunes.hpp"
#include "UtunesServer.hpp"
#include "controllers/HomeController.hpp"
#include "controllers/SignupController.hpp"
class RouteHandler
{
public:
	RouteHandler(Utunes* _utunes) : utunes(_utunes) {}
	void run();
private:
	Utunes* utunes;
	void load_css(UtunesServer* server);
	void load_img(UtunesServer* server);
};
#endif