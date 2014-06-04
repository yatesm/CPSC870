#ifndef MANAGER__H
#define MANAGER__H
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
using std::cout; using std::endl; 
using std::string;
using std::vector;

#include "world.h"
#include "sprite.h"
#include "ioManager.h"
#include "factory.h"
//#include "musicFactory.h"
#include "gametimer.h"
//#include "soundManager.h"
#include "explosion.h"
#include "bullet.h"
#include "collisionStrategy.h"
#include "fleeStrategy.h"
#include "stats.h"

class Manager {
public:
  Manager ();
  virtual ~Manager ();
   
  void loadSprite(vector<Sprite *> &v, const char * filename, const char *directory);
  void loadExplosion(vector<Sprite *> &v, const char *filename, const char *directory);
  void loadBullets(vector<Bullet> &v, const char * filename, const char *directory);
  void loadStats(Stats *stats, const char * filename, const char *directory);
  
  void saveBullets(const vector<Bullet> &v, const char * filename, const char *directory) const;
  void saveSprite(const vector<Sprite *> &v, const char *filename, const char *directory) const; 
  void saveStats(Stats *stats, const char * filename, const char *directory);
  
  virtual void drawAndUpdateSprite(vector<Sprite *> &v, Uint32 ticks);  
    
  virtual void callHelpScreen() = 0;
  virtual void callEndGameScreen() = 0;
  virtual void initializeGame() = 0;
  virtual void loadFrames() = 0;
  virtual void play() = 0;  
  
protected:
  IOManager *io;
  Factory *fact;
/*  SoundManager *sManager;  
  MusicFactory *mFact;*/
  CollisionSingleton *collisions;
  FleeSingleton *flee;
  SDL_Surface * const screen;
  bool done;
  
  GameTimer timer;
  bool loadFlag;
  bool amPlaying;
private:
  Manager(const Manager&);
  Manager& operator=(const Manager&);
};
#endif
