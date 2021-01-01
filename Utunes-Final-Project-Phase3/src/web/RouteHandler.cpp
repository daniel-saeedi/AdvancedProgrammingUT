#include "RouteHandler.hpp"
const std::string PUBLIC_DIR = "../../public";
void RouteHandler::run()
{
	srand(time(NULL));
	try
	{
		UtunesServer server(2022);
		server.setNotFoundErrPage(PUBLIC_DIR+"/404.html");
		server.run();
	}
	catch (Server::Exception e)
	{
		std::cerr << e.getMessage() << std::endl;
	}
}