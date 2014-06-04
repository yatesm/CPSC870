#ifndef SINGLE__H
#define SINGLE__H
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include <sstream>
using std::string;

class IOManager {
public:
  ~IOManager() { 
    TTF_CloseFont(font);
    SDL_FreeSurface(screen);
  }
  SDL_Surface * getScreen() const { return screen; }
  void toggleFullscreen();
  static IOManager* getInstance();
  void changeFontSize(int);
  void revertFontSizeToOriginal();

  SDL_Surface* loadAndSet(const string& filename, bool setcolorkey);

  void printMessageAt(const string& msg, Uint32 x, Uint32 y);
  void printMessageCenteredAt(const string& msg, Uint32 y);
  void printMessageValueAt(const string& msg, float value, 
         Uint32 x, Uint32 y);
	void printMessageValueAt(const string& msg, int value, 
   	  Uint32 x, Uint32 y);
  void printStringAfterMessage(const string&, Uint32 x, Uint32 y);
  void buildString(SDL_Event);
  void clearString() { inputString = ""; }
  const string& getString() const { return inputString; }
private:
  IOManager();
  IOManager(const IOManager&);
  IOManager& operator=(const IOManager&);
  
  int height;
  int width;
  SDL_Surface *screen;
  unsigned maxString;
  int originalSize;
  bool fullscreen;
  static IOManager* instance;
  TTF_Font *font;
  string inputString;
};
#endif
