#ifndef FACTORY__H
#define FACTORY__H

#include <map>

#include "frame.h"
#include "ioManager.h"
#include "SDL/SDL.h"

using std::map;


class Factory {
   public:
      static Factory* getInstance();
      ~Factory();
		Frame* getFrame(const string& s);
      Frame* makeFrame(const string& s);
		SDL_Surface* getSurface(const string& s);
      SDL_Surface* makeSurface(const string& s);
      
      string getSurfaceKey(const SDL_Surface *s);
      string getFrameKey(const Frame *s);
      void makeSprite(const SpriteData& s);
      void printFrameMap();
      
   private:
		Factory() : frameMap(), surfaceMap(), io(IOManager::getInstance()) {}
      Factory(const Factory& f);
      Factory& operator=(const Factory& f);
	   
      std::map<const string, Frame *> frameMap;
      std::map<const string, SDL_Surface *> surfaceMap;
      IOManager *io;
      static Factory *instance;
};
#endif
