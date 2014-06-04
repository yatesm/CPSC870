#ifndef ZOMBIECHASEMANAGER__H
#define ZOMBIECHASEMANAGER__H
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
using std::cout; using std::endl; 
using std::string;
using std::vector;

#include "manager.h"
#include "viewport.h"
#include "sprite.h"
#include "people.h"
#include "zombie.h"
#include "explosion.h"
#include "fleeStrategy.h"
#include "collisionStrategy.h"
#include "stats.h"
#include "parallax.h"

class ZombieChaseManager : public Manager {
public:
  ZombieChaseManager();
  virtual ~ZombieChaseManager();
  
  virtual void loadFrames();
  void initializePeople();
  void initializeZombies();
  void initializeClouds();
  void initializeMasks();

  virtual void play();

  void findTracked();
  void trackSprite(const unsigned int i);

  virtual void drawAndUpdateSprite(vector<Sprite *> &v, Uint32 ticks);
  void drawAndUpdateBullets(Uint32 ticks);
  void drawAndUpdateMask();
  
  void makeBullet(int x, int y);
  void bulletsExplodeZombies(const unsigned int i);
  void bulletsExplodePeople(const unsigned int i);
  void bulletsExplodeSprite(Sprite &s);
  void cullBullets();

  void makeSplats(Sprite& s);  

  void drawZombieBar(const Uint32 color1, const Uint32 color2);
  void drawPeopleBar(const Uint32 color1, const Uint32 color2);
  
  void zombiesFindDinner();
  void zombiesEatingCheck();
  void zombiesEatPeople(int i);  
  void peopleRunAway();
  
  virtual void callHelpScreen();
  virtual void callEndGameScreen();
  void handleEndGameText();
  
  void initializeGame();
  void KILL_YOURSELF();
  void BIRTH_YOURSELF();
  void REBIRTH_YOURSELF();
  
protected:
  Game *game;
  
  SDL_Surface * bgSurface;
  const Frame background;

  vector<Sprite *> zombies;
  vector<Sprite *> people;
  vector<Sprite *> splats;
  vector<Sprite *> splosions;
  vector<Bullet> bullets;
  Sprite* activeSprite;
  unsigned int activeSpriteIndex;
  World world;
  Viewport *view;  
  
  Sprite * mask;
  Sprite * collisionMask;
  Stats* stats;
  Parallax clouds;

  int playerType;
  
private:
  ZombieChaseManager(const ZombieChaseManager&);
  ZombieChaseManager& operator=(const ZombieChaseManager&);
};
#endif
