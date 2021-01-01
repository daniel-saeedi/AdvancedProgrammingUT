#ifndef UTUNES_SERVER_H
#define UTUNES_SERVER_H
#include "APHTTP/server/server.hpp"

class UtunesServer : public Server {
public:
  UtunesServer(int port = 5000);
};

#endif
