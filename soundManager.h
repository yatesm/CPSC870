#ifndef SOUNDMANAGER__H
#define SOUNDMANAGER__H
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <vector>

#include "musicFactory.h"

using std::vector;

class SoundManager {

   public:
		static SoundManager* getInstance();
   	~SoundManager();
      void startMusic(int i);
      void stopMusic()   { Mix_HaltMusic(); }      // stop all sounds
      void toggleMusic();   // stop all sounds
      void operator[](int);  // play the indexed sound
   
      void setVolume(const int v) { volume = v; }
      void setAudioRate(const int rate) { audioRate = rate; }
      void setAudioChannels(const int channels) { audioChannels = channels; }
      void setAudioBuffers(const int buffers) { audioBuffers = buffers; }
      
      int getVolume() const { return volume; }
      int getAudioRate() const { return audioRate; }
      int getAudioChannels() const { return audioChannels; }
      int getAudioBuffers() const { return audioBuffers; }
		
		void load();
		void loadSounds();
		void loadMusic();
   private:
   	static SoundManager* instance;
   	MusicFactory *mFact;
      int volume;
      int currentSound;
      int audioRate;
      int audioChannels;
      int audioBuffers;
      
      std::vector<Mix_Music*> music;
      std::vector<int> musicChannels;
      std::vector<Mix_Chunk*> sounds;
      std::vector<int> channels;

      SoundManager();
      SoundManager(const SoundManager&);
      SoundManager operator=(const SoundManager&);
};
#endif
