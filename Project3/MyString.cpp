#include "myString.hpp"

MyString::MyString(int _x, int _y, int _fontSize,std::string _field_name)
    : x(_x), y(_y), fontSize(_fontSize), field_name(_field_name) {}

string MyString::textToDisplay() { return field_name + ":  "+ inputString; }

void MyString::eraseLastChar() {
  if (inputString.size() > 0)
    inputString.erase(inputString.size() - 1);
}

void MyString::addChar(char c) {
  if (inputString.size() < MAX_STRING_LENGTH)
    inputString += c;
}

void MyString::drawString(Window *win) {
  win->show_text(textToDisplay(), Point(x, y), WHITE, FONT_SANSSERIF, fontSize);
}

string MyString::getString() { return inputString; }
