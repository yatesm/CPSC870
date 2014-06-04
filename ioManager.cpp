#include <iostream>
#include <iomanip>

#include "ioManager.h"
#include "game.h"

using std::string;

IOManager* IOManager::getInstance() {
  if (!instance) instance = new IOManager(); 
  return instance;
}

IOManager::IOManager( ) : height(Game::getInstance()->getViewHeight()),
  width(Game::getInstance()->getViewWidth()), 
  screen(SDL_SetVideoMode(width, height, 16, SDL_HWSURFACE)),
  maxString(Game::getInstance()->getMaxString()),
  originalSize(Game::getInstance()->getFontSize()), fullscreen(false),
  font( NULL ), inputString("")  {
	 if (screen == NULL) { 
    throw string("Unable to set video mode"); 
  }
  if ( TTF_Init() == -1 ) {
    throw string("TTF_Init failed: ") + TTF_GetError();
  }
  font = TTF_OpenFont("font/parentssuck.ttf", originalSize);
  if ( !font ) {
    throw string("TTF_OpenFont failed: ") + TTF_GetError();
  }
  SDL_EnableUNICODE( SDL_ENABLE );
  atexit(SDL_Quit);
  atexit(TTF_Quit);
}

void IOManager::toggleFullscreen() {
  throw string("Don't use this.");
  if ( fullscreen ) {
    screen = SDL_SetVideoMode( width, height, 16, SDL_HWSURFACE );
  } 
  else {
    screen = SDL_SetVideoMode(width, height, 16, SDL_HWSURFACE | SDL_FULLSCREEN);
  }
  fullscreen = !fullscreen;
}

void IOManager::revertFontSizeToOriginal( ) {
  font = TTF_OpenFont("font/parentssuck.ttf", originalSize);
  if ( !font ) {
    throw string("TTF_OpenFont failed: ") + TTF_GetError();
  }
}

void IOManager::changeFontSize(int newSize ) {
  font = TTF_OpenFont("font/parentssuck.ttf", newSize);
  if ( !font ) {
    throw string("TTF_OpenFont failed: ") + TTF_GetError();
  }
}

SDL_Surface* IOManager::loadAndSet(const string& filename, bool setcolorkey) {
  SDL_Surface *tmp = IMG_Load(filename.c_str());
  if (tmp == NULL) {
    throw string("Unable to load bitmap ")+filename;
  }
  if ( setcolorkey ) {
    Uint32 colorkey = SDL_MapRGB(tmp->format, 255, 0, 255);
    SDL_SetColorKey(tmp, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey);
  }
  // Optimize the strip for fast display
  SDL_Surface *image = SDL_DisplayFormat(tmp);
  if (image == NULL) {
    image = tmp;
  } 
  else {
    SDL_FreeSurface(tmp);
  }
  return image;
}

void IOManager::printMessageAt(const string& msg, Uint32 x, Uint32 y) {
   SDL_Rect dest = {x,y,0,0};
   SDL_Color color = {255, 0, 0, 0};
   SDL_Surface * stext = TTF_RenderText_Blended(font, msg.c_str(), color);
   if (stext) {
     SDL_BlitSurface( stext, NULL, screen, &dest );
     SDL_FreeSurface(stext);
   }
   else {
     throw 
     string("Couldn't allocate text sureface in printMessageAt");
   }
}

void IOManager::printMessageCenteredAt( const string& msg, Uint32 y) {
   SDL_Color color = {255, 0, 0, 0};
   SDL_Surface *stext = TTF_RenderText_Blended(font, msg.c_str(), color);
   if (stext) {
     Uint32 x = ( width - stext->w ) / 2;
     SDL_Rect dest = {x,y,0,0};
     SDL_BlitSurface( stext, NULL, screen, &dest );
     SDL_FreeSurface(stext);
   }
   else {
     throw 
     string("Couldn't allocate text sureface in printMessageCenteredAt");
   }
}

void IOManager::printMessageValueAt(const string& msg, float value, 
     Uint32 x, Uint32 y) {
   std::stringstream strm;
   std::string message = msg;
   strm.setf(std::ios::fixed, std::ios::floatfield);
   strm.setf(std::ios::showpoint);
   strm << message << std::setprecision(2);
   strm << value << "\0";
   message = strm.str();
   SDL_Rect dest = {x,y,0,0};
   SDL_Color color = {255, 0, 0, 0};
   SDL_Surface *stext = TTF_RenderText_Blended(font, message.c_str(), color);
   if (stext) {
     SDL_BlitSurface( stext, NULL, screen, &dest );
     SDL_FreeSurface(stext);
   }
   else {
     throw 
     string("Couldn't allocate text sureface in printMessageValueAt");
   }
}

void IOManager::printMessageValueAt(const string& msg, int value, 
     Uint32 x, Uint32 y) {
   std::stringstream strm;
   std::string message = msg;
   strm << message;
   strm << value << "\0";
   message = strm.str();
   SDL_Rect dest = {x,y,0,0};
   SDL_Color color = {255, 0, 0, 0};
   SDL_Surface *stext = TTF_RenderText_Blended(font, message.c_str(), color);
   if (stext) {
     SDL_BlitSurface( stext, NULL, screen, &dest );
     SDL_FreeSurface(stext);
   }
   else {
     throw 
     string("Couldn't allocate text sureface in printMessageValueAt");
   }
}

void IOManager::printStringAfterMessage( const string& msg,
       Uint32 x, Uint32 y ) {
   printMessageAt(msg+inputString, x, y);
}

void IOManager::buildString(SDL_Event event) {
  if( inputString.size() <= maxString ) {
    unsigned ch = event.key.keysym.sym;
    if (isalpha(ch) || isdigit(ch) || ch == ' ') {
      inputString += char(event.key.keysym.unicode);
    }
  }     
  if( event.key.keysym.sym == SDLK_BACKSPACE
      && inputString.length() > 0 ) {
      // remove a character from the end
      int length = inputString.size();
      inputString.erase( length - 1 );
  }
}

