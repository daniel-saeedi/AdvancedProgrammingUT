#ifndef SIGNUP_HANDLER_H
#define SIGNUP_HANDLER_H
#include <iostream>
#include <string>
#include "../../../server/server.hpp"
#include "../../User.hpp"
#include "../../Utunes.hpp"
class SignupHandler : public RequestHandler
{
public:
  SignupHandler(Utunes* _utunes) : utunes(_utunes) {};
  Response* callback(Request *);
private:
  Utunes* utunes;
};
#endif