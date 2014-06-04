#include <SDL/SDL.h>
#include "soundManager.h"
#include "musicFactory.h"

#include<iostream>

using std::cout;
using std::endl;

const string sound1 = "sounds/groans/groan1.wav";  //0
const string sound2 = "sounds/groans/groan2.wav";
const string sound3 = "sounds/groans/groan3.wav";
const string sound4 = "sounds/groans/groan4.wav"; //3
const string sound5 = "sounds/screams/scream1.wav"; //4
const string sound6 = "sounds/screams/scream2.wav";
const string sound7 = "sounds/screams/scream3.wav";
const string sound8 = "sounds/screams/scream4.wav";	
const string sound9 = "sounds/screams/scream5.wav";
const string sound10 = "sounds/screams/scream6.wav";	
const string sound11 = "sounds/screams/scream7.wav";
const string sound12 = "sounds/screams/scream8.wav";	
const string sound13 = "sounds/screams/scream9.wav";
const string sound14 = "sounds/screams/scream10.wav"; //12							
const string sound15 = "sounds/misc/gun.wav";

SoundManager* SoundManager::getInstance() {
	if(!instance) instance = new SoundManager();
	return instance;
}

SoundManager::SoundManager() : mFact(MusicFactory::getInstance()),
  volume(MIX_MAX_VOLUME/4), currentSound(-1), 
  audioRate(22050), audioChannels(2), audioBuffers(4096), music(), musicChannels(), 
  sounds(), channels()
{
	 if(Mix_OpenAudio(audioRate, MIX_DEFAULT_FORMAT, audioChannels, audioBuffers))
   {
      	throw std::string("Unable to open audio!");
  	}
  	mFact->initializeFiles();
  	load();
}

void SoundManager::load() {
  	loadSounds();
  	for (unsigned int i = 0; i < sounds.size(); ++i) 
     	channels.push_back(i); 
   loadMusic();
   for (unsigned int i = 0; i < music.size(); ++i)
   	musicChannels.push_back(i);  	 
  	cout<<"Just to let you know, sounds.size() == "<<sounds.size();
}

void SoundManager::loadSounds() {
	sounds.push_back(mFact->getSound(sound1));
	sounds.push_back(mFact->getSound(sound2));	
	sounds.push_back(mFact->getSound(sound3));
	sounds.push_back(mFact->getSound(sound4));	
	sounds.push_back(mFact->getSound(sound5));
	sounds.push_back(mFact->getSound(sound6));	
	sounds.push_back(mFact->getSound(sound7));
	sounds.push_back(mFact->getSound(sound8));	
	sounds.push_back(mFact->getSound(sound9));
	sounds.push_back(mFact->getSound(sound10));	
	sounds.push_back(mFact->getSound(sound11));	
	sounds.push_back(mFact->getSound(sound12));			
	sounds.push_back(mFact->getSound(sound13));					
	sounds.push_back(mFact->getSound(sound14));
	sounds.push_back(mFact->getSound(sound15));	
}

void SoundManager::loadMusic() {

}

SoundManager::~SoundManager() 
{
   Mix_HaltMusic();
   music.clear();
   sounds.clear();
}

void SoundManager::toggleMusic() 
{
   if(Mix_PausedMusic()) 
      Mix_ResumeMusic(); 
   else 
      Mix_PauseMusic(); 
}

void SoundManager::operator[](int index) {
  if (currentSound >= 0) Mix_HaltChannel(currentSound);
  currentSound = index;
  Mix_VolumeChunk(sounds[index], volume);
  channels[index] = 
     Mix_PlayChannel(-1, sounds[index], 1);
}

void SoundManager::startMusic(int i) 
{
   Mix_VolumeMusic(volume);
   Mix_PlayMusic(music[i], 10);
}
