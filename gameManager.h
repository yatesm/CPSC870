#ifndef GAMEMANAGER__H
#define GAMEMANAGER__H

#include <cmath>
#include <ctime>
#include <string>

#include "manager.h"
#include "manager.h"
#include "viewport.h"
#include "world.h"
#include "sprite.h"

class GameManager : public Manager {
	public:
		GameManager();
		virtual ~GameManager();
		
	   virtual void callHelpScreen() { }
		virtual void callEndGameScreen() { }
		virtual void initializeGame() {}
		virtual void loadFrames();
		virtual void play();
		const int getGameSelection() const { return gameSelection; }
	private:
		int gameSelection;		
		SDL_Surface * bgSurface;
		const Frame background;
		World world;		
		Game *game;
		Viewport *view;		
		GameManager(const GameManager&);
		GameManager operator=(const GameManager&);
};
#endif
