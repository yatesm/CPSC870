#include "gameManager.h"

const string zombieChaseButtonSurfaceString = "images/zombieChaseButton.bmp";
const string zombieDefenseButtonSurfaceString = "images/zombieDefenseButton.bmp";
const string exitButtonSurfaceString = "images/exitButton.bmp";
const string bgSurfaceString = "images/bground.bmp";

GameManager::~GameManager() {
   delete fact;
   delete io;
//   delete mFact;
   delete game;
   delete collisions;
   delete flee;
}

GameManager::GameManager() : Manager(), gameSelection(0), 
	bgSurface(fact->makeSurface(bgSurfaceString)), 
	background(fact->makeFrame(bgSurfaceString)),
	world(fact->getFrame(bgSurfaceString)), game(Game::getInstance()), 
	view(Viewport::getInstance())
	{
   SDL_WM_SetCaption( "The Zombie Apocalypse Is Upon Us!", NULL );   
   SDL_ShowCursor(1);
   atexit(SDL_Quit);
	loadFrames();
}
								 
void GameManager::play() {
	float sx = view->getX() + 200, sy = view->getY();
	Uint32 x, y;
	bool keyDown = false, mouseDown = false;	
	SDL_Event event;
   Sprite zombieDefenseButton(sx, sy + 80, 0, 0, 
   	fact->getFrame(zombieDefenseButtonSurfaceString));
   Sprite zombieChaseButton(sx, sy + 160, 0, 0, 
   	fact->getFrame(zombieChaseButtonSurfaceString));
   Sprite exitButton(sx, sy + 240, 0, 0, 
   	fact->getFrame(exitButtonSurfaceString));	
	while(true) {
   	   world.draw();   			
			zombieChaseButton.draw();
			zombieDefenseButton.draw();
			exitButton.draw();
         SDL_Flip(screen);
   		SDL_PollEvent(&event);         
	      if(event.type == SDL_MOUSEBUTTONUP)
	         mouseDown = false;
   	   if(event.type == SDL_MOUSEBUTTONDOWN && mouseDown == false) {
	      	mouseDown = true;
	      	x = event.motion.x + static_cast<int>(view->getX());
	      	y = event.motion.y + static_cast<int>(view->getY());
	      	if(x > zombieChaseButton.getX() && x < zombieChaseButton.getX() + zombieChaseButton.getFrame()->getWidth()) {
	      		if(y > zombieChaseButton.getY() && y < zombieChaseButton.getY() + zombieChaseButton.getFrame()->getHeight()) {
	      			cout<<"Triggered Zombie Chase Return"<<endl;
						gameSelection = 1;
	      		   return;
	      		}
	      		else if(y > zombieDefenseButton.getY() && y < zombieDefenseButton.getY() + zombieDefenseButton.getFrame()->getHeight()) {
	      			cout<<"Triggered Zombie Defense Return"<<endl;
						gameSelection = 2;
						return;	
	      		}
	      		else if(y > exitButton.getY() && y < exitButton.getY() + exitButton.getFrame()->getHeight()) {
	      			cout<<"Triggered Quit Return"<<endl;
	      		   gameSelection = 0;
	      		   return;
	      		}
	      	}
		   }
      	if(event.type == SDL_QUIT) { done = true; break; }
      	if(event.type == SDL_KEYUP) keyDown = false;
         if(event.type == SDL_KEYDOWN) {
               switch(event.key.keysym.sym) {
                  case SDLK_q:
                  case SDLK_ESCAPE:
                      done = true;
                      gameSelection = 0;
                      return;
                  case SDLK_c:
                  	if(keyDown == false)
                  		gameSelection = 1;
                  	return;
            		case SDLK_d:
            			if(keyDown == false)
		      		   	gameSelection = 2;
		      		  	return;
            		default: break;            		 	
            }
            keyDown = true;
      }
   }  
}

void GameManager::loadFrames() {
	fact->makeSprite(game->getData(zombieChaseButtonSurfaceString));
	fact->makeSprite(game->getData(zombieDefenseButtonSurfaceString));
	fact->makeSprite(game->getData(exitButtonSurfaceString));
}
