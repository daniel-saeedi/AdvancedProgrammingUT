#ifndef __MY_STRING__
#define __MY_STRING__
#include "rsdl.hpp"
#include <iostream>
#include <string>

using namespace std;

#define MAX_STRING_LENGTH 10
#define FONT_SANSSERIF "Assets/FreeSans.ttf"

class MyString {
public:
  MyString(int _x, int _y, int _fontSize,std::string _field_name);
  string textToDisplay();
  void eraseLastChar();
  void addChar(char c);
  void drawString(Window *win);
  string getString();

private:
  string inputString;
  int fontSize;
  int x;
  int y;
  std::string field_name;
};
#endif
