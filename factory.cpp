#include "factory.h"
#include <iostream>

Frame* Factory::getFrame(const string& s) { 
   std::map<const string, Frame *>::iterator ptr;
   ptr = frameMap.find(s);
   return ptr->second;
}

Frame* Factory::makeFrame(const string& s) {
	std::map<const string, SDL_Surface *>::iterator it = surfaceMap.find(s);
   SDL_Surface *tempSurface;
   if(it == surfaceMap.end()) {
   	tempSurface = makeSurface(s);
  	}
  	else {
  		tempSurface = getSurface(s);
  	}
  	if(frameMap.count(s) == 0)
		frameMap.insert(std::map<const string, Frame *>::value_type(s, new Frame(tempSurface, io->getScreen(), tempSurface->w, tempSurface->h, 0, 0)));
   return(getFrame(s));
}

SDL_Surface* Factory::getSurface(const string& s) {
   std::map<const string, SDL_Surface *>::iterator ptr;
   ptr = surfaceMap.find(s);
   return ptr->second;
}
SDL_Surface* Factory::makeSurface(const string& s) {
   map<const string, SDL_Surface *>::iterator it = surfaceMap.find(s);
   if(it == surfaceMap.end()) {
	   surfaceMap.insert(std::map<const string, SDL_Surface *>::value_type(s, io->loadAndSet(s, true)));
	}
	 return getSurface(s);
}

void Factory::makeSprite(const SpriteData& s) {
	map<const string, SDL_Surface *>::iterator it = surfaceMap.find(s.getFname());
	if(it == surfaceMap.end())
		surfaceMap.insert(std::map<const string, SDL_Surface *>::value_type(s.getFname(), io->loadAndSet(s.getFname(), s.getColorKey())));
	map<const string, Frame *>::iterator it2 = frameMap.find(s.getFname());
	if(it2 == frameMap.end())
		frameMap.insert(std::map<const string, Frame *>::value_type(s.getFname(), new Frame(getSurface(s.getFname()), io->getScreen(), s.getWidth(), s.getHeight(), s.getSpriteSrcX(), s.getSpriteSrcY())));
}

Factory* Factory::getInstance() {
   if(!instance) instance = new Factory();
   return(instance);
}

Factory::~Factory() {
   for(map<const string, Frame *>::iterator it = frameMap.begin(); it != frameMap.end(); ++it)
      delete (*it).second;
   frameMap.clear();

   for(map<const string, SDL_Surface *>::iterator it = surfaceMap.begin(); it != surfaceMap.end(); ++it)
      SDL_FreeSurface((*it).second);
   surfaceMap.clear();
}

void Factory::printFrameMap() {
   for(map<const string, Frame *>::iterator it = frameMap.begin(); it != frameMap.end(); ++it)
      cout<<it->first<<" "<<it->second->getWidth()<<" "<<it->second->getHeight()<<" "<<it->second->getSourceX()<<" "<<it->second->getSourceY()<<endl;
}

string Factory::getSurfaceKey(const SDL_Surface* s) {
	std::map<const string, SDL_Surface *>::iterator it = surfaceMap.begin();
	while(it != surfaceMap.end()) {
		if(it->second == s)
			return (it->first);
		++it;	
	}
	return NULL;
}

string Factory::getFrameKey(const Frame *s) {
	std::map<const string, Frame *>::iterator it = frameMap.begin();
	while(it != frameMap.end()) {
		if(it->second == s)
			return (it->first);
		++it;
	}
	return NULL;
}
