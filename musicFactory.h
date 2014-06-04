#ifndef MUSICFACTORY__H
#define MUSICFACTORY__H

#include <map>
#include <SDL/SDL_mixer.h>
#include <string>

#include "ioManager.h"
#include "SDL/SDL.h"
#include "game.h"


using std::map;
using std::string;

class MusicFactory {
   public:
      static MusicFactory* getInstance();
      ~MusicFactory();
      Mix_Music* makeMusic(const string& s);
      Mix_Music* getMusic(const string& s); 
      Mix_Chunk* makeSound(const string& s); 
      Mix_Chunk* getSound(const string& s); 
		void initializeFiles();
   private:
		MusicFactory();
      MusicFactory(const MusicFactory& f);
      MusicFactory& operator=(const MusicFactory& f);
	   
      std::map<string, Mix_Music *> musicMap;
      std::map<string, Mix_Chunk *> soundMap;
      IOManager *io;
      static MusicFactory *instance;
};
#endif
