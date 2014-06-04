#ifndef ZOMBIEDEFENSEMANAGER__H
#define ZOMBIEDEFENSEMANAGER__H
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
using std::cout; using std::endl; 
using std::string;
using std::vector;

#include "manager.h"
#include "viewport.h"
#include "people.h"
#include "zombie.h"
#include "fleeStrategy.h"
#include "collisionStrategy.h"
#include "stats.h"
#include "parallax.h"

class ZombieDefenseManager : protected Manager {
	public:
		ZombieDefenseManager();
		virtual ~ZombieDefenseManager();
		
		virtual void callHelpScreen();
		virtual void callEndGameScreen();
		
		virtual void initializeGame();
		virtual void loadFrames();
		
		virtual void play();  
		
		void placeInitialHumans();
		void placeInitialZombies();
		void handleEndGameText();
		
		void cullBullets();
		void drawAndUpdateBullets(Uint32 ticks);
		void bulletsExplodeSprite(Sprite &s);
		void zombiesEatingCheck();
		void makeSplats(Sprite& s);
		void zombiesEatPeople(int i);
		
		void KILL_YOURSELF();
		void BIRTH_YOURSELF();
		void REBIRTH_YOURSELF();
		
		void zombiesChase();
		void peopleShoot();
		void makeBullet(const Sprite& shooter, const Sprite& target);
		
		void drawAndUpdateZombies(Uint32 ticks);
	protected:
		Game *game;
  
		SDL_Surface * bgSurface;
		const Frame background;	
		
		Sprite *lastFemaleOnEarth;
		vector<Sprite *> zombies;
		vector<Sprite *> people;
		vector<Sprite *> splats;
		vector<Sprite *> splosions;
		vector<Bullet> bullets;	
		World world;
		bool loseCondition;
		Viewport *view;
  		Stats* stats;
		
	private:
		ZombieDefenseManager(const ZombieDefenseManager&);
		ZombieDefenseManager& operator=(const ZombieDefenseManager&);
};
#endif
