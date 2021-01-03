#ifndef LIKE_HANDLER_H
#define LIKE_HANDLER_H
#include <iostream>
#include <string>
#include <map>
#include "../../../server/server.hpp"
#include "../../Song.hpp"
#include "../../Utunes.hpp"
class LikeHandler : public RequestHandler 
{
public:
  LikeHandler(Utunes* _utunes) : utunes(_utunes){}
  Response* callback(Request* request);
private:
  Utunes *utunes;
};
#endif