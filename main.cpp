// Brian Malloy        Game Construction

#include "zombieChaseManager.h"
#include "zombieDefenseManager.h"
#include "gameManager.h"

#include<iostream>

Viewport *Viewport::instance = NULL;
IOManager *IOManager::instance = NULL;
Factory *Factory::instance = NULL;
Game* Game::instance = NULL;
ParseXML* ParseXML::instance = NULL;
//MusicFactory *MusicFactory::instance = NULL;
CollisionSingleton *CollisionSingleton::instance = NULL;
FleeSingleton *FleeSingleton::instance = NULL;
//SoundManager *SoundManager::instance = NULL;

int main(int, char*[]) {
   try {
     	     if (SDL_Init(SDL_INIT_VIDEO/* | SDL_INIT_AUDIO*/) != 0)
      		 throw string("Unable to initialize SDL: ");
 			GameManager gameManager;
 			ZombieDefenseManager *zombieDefenseGame;
 			ZombieChaseManager *zombieChaseGame;
 			int selection = 1;
 			while(selection != 0) {
 				gameManager.play();
 				selection = gameManager.getGameSelection();
 				switch(selection) {
 					case 0:
 						return 0;
 						break;
 					case 1:
 						zombieChaseGame = new ZombieChaseManager();
 						zombieChaseGame->play();
 						delete zombieChaseGame;
 						break;
 					case 2:
 						zombieDefenseGame = new ZombieDefenseManager();
 						zombieDefenseGame->play();
 						delete zombieDefenseGame;
 						break;
 					default:
 						break;
 				}
 			}
 			return 0;
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
