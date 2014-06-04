#include "musicFactory.h"
#include <SDL/SDL_mixer.h>
#include <iostream>

MusicFactory* MusicFactory::getInstance() {
   if(!instance) instance = new MusicFactory();
   return(instance);
}

MusicFactory::MusicFactory() : musicMap(), soundMap(), io(IOManager::getInstance()) {}

void MusicFactory::initializeFiles() {
	std::multimap<string, string> soundDataMap = Game::getInstance()->getSoundData();
	std::multimap<string, string>::const_iterator soundMapIt = soundDataMap.begin();
	while(soundMapIt != soundDataMap.end()) {
   	makeSound(soundMapIt->second);
		++soundMapIt;
	}

	std::multimap<string, string> musicDataMap = Game::getInstance()->getMusicData();
	std::multimap<string, string>::iterator musicMapIt = musicDataMap.begin();
	while(musicMapIt != musicDataMap.end()) {
		makeMusic(musicMapIt->second);
		++musicMapIt;
	}
}

MusicFactory::~MusicFactory() {
   for(map<const string, Mix_Music *>::iterator it = musicMap.begin(); it != musicMap.end(); ++it)
      Mix_FreeMusic((*it).second);
   musicMap.clear();

   for(map<const string, Mix_Chunk *>::iterator it = soundMap.begin(); it != soundMap.end(); ++it)
      Mix_FreeChunk((*it).second);
   soundMap.clear();
}

Mix_Music* MusicFactory::makeMusic(const string& s) {
   map<const string, Mix_Music *>:: iterator it = musicMap.find(s);   
   if(it == musicMap.end()) {
	   Mix_Music* tempMusic;   
   	if((tempMusic = Mix_LoadMUS(s.c_str())) == NULL)
	 		std::cout<<"Unable to load file: "<<s<<std::endl;
	 	else
	 		musicMap.insert(std::map<const string, Mix_Music *>::value_type(s, tempMusic));
	 	return(tempMusic);
	}
	else
		return(it->second);
}

Mix_Music* MusicFactory::getMusic(const string& s) {
   map<const string, Mix_Music *>:: iterator it = musicMap.find(s);
   if(it == musicMap.end())
   	makeMusic(s);
  	it = musicMap.find(s);
  	return(it->second);
}

Mix_Chunk* MusicFactory::makeSound(const string& s) {
   map<const string, Mix_Chunk *>:: iterator it = soundMap.find(s);	
   if(it == soundMap.end()) {
 		Mix_Chunk* tempSound;
   	if((tempSound = Mix_LoadWAV(s.c_str())) == NULL) {
			fprintf(stderr, "Unable to load WAV file: %s\n", Mix_GetError());
			cout<<"Filename is "<<s<<endl;
		}
	 	else
	 		soundMap.insert(std::map<const string, Mix_Chunk *>::value_type(s, tempSound));
	 	return(tempSound);
	}
	else
		return(it->second);
}

Mix_Chunk* MusicFactory::getSound(const string& s) {
   map<const string, Mix_Chunk *>:: iterator it = soundMap.find(s);
   if(it == soundMap.end())
   	makeSound(s);
	it = soundMap.find(s);
  	return(it->second);
}
