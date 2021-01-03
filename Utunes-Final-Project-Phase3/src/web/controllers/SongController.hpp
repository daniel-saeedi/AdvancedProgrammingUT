#ifndef SONG_CONTROLLER_H
#define SONG_CONTROLLER_H
#include <iostream>
#include <string>
#include <map>
#include "../../../server/server.hpp"
#include "../../Song.hpp"
#include "../../Utunes.hpp"
class SongController : public TemplateHandler 
{
public:
  SongController(std::string file_path,Utunes* _utunes) : TemplateHandler(file_path),utunes(_utunes){}
  std::map<std::string,std::string> handle(Request *req);
private:
  Utunes *utunes;
  std::string recommendation_html(std::string title,std::string artist,int id,int year);
  std::string get_recom(Song* current_song);
  std::string get_like_button(Song* song);
};
#endif