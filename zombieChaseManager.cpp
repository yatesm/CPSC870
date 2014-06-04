#include <cmath>
#include <ctime>
#include <string>

#include "zombieChaseManager.h"
#include "explosion.h"
//#include <SDL/SDL_draw.h>

using std::string;

const string bgSurfaceString ("images/bground.bmp");
const string zombieFaceSurfaceString("images/zombieFace.bmp");
const string humanFaceSurfaceString ("images/humanFace.bmp");
const string bloodSplatSurfaceString ("images/bloodsplat.bmp");
const string bloodSplat2SurfaceString ("images/bloodsplat2.bmp");
const string bloodSplat3SurfaceString ("images/bloodsplat3.bmp");
const string bloodSplat4SurfaceString ("images/bloodsplat4.bmp");
const string scaredFaceSurfaceString ("images/scaredFace.bmp");
const string freakedFaceSurfaceString ("images/freakedOutFace.bmp");
const string bulletSurfaceString ("images/bullet.bmp");
const string cloud1SurfaceString ("images/cloud1.bmp");
const string cloud2SurfaceString ("images/cloud2.bmp");
const string cloud3SurfaceString ("images/cloud3.bmp");
const string cloud4SurfaceString ("images/cloud4.bmp");
const string loadButtonSurfaceString("images/loadButton.bmp");
const string humanButtonSurfaceString("images/humanButton.bmp");
const string zombieButtonSurfaceString("images/zombieButton.bmp");
const string helpButtonSurfaceString("images/helpButton.bmp");
const string returnButtonSurfaceString("images/returnButton.bmp");

void ZombieChaseManager::KILL_YOURSELF() {
   for(vector<Sprite *>::iterator it(zombies.begin()); it != zombies.end(); ++it)
      delete *it;
	zombies.clear();
   for(vector<Sprite *>::iterator it(people.begin()); it != people.end(); ++it)
      delete (*it);
	people.clear();
   for(vector<Sprite *>::iterator it(splats.begin()); it != splats.end(); ++it)
      delete (*it);
	splats.clear();
	for(vector<Sprite *>::iterator it(splosions.begin()); it != splosions.end(); ++it)
		delete (*it);		
	splosions.clear();
	bullets.clear();
	delete stats;
}

void ZombieChaseManager::REBIRTH_YOURSELF() {
   	loadSprite(zombies, "zombie", "chase");
   	loadSprite(people, "people", "chase");
   	findTracked();
   	loadStats(stats, "stat", "chase");
   	loadSprite(splats, "splat", "chase");   	
   	loadBullets(bullets, "bullet", "chase");
   	loadExplosion(splosions, "splosion", "chase");
}

void ZombieChaseManager::BIRTH_YOURSELF() {
	   initializeZombies();      
	   initializePeople();
	   if(playerType == 0) {
	   	activeSprite = people[activeSpriteIndex];
	   	stats = new PlayerStats();
		}   
		else {
			activeSprite = zombies[activeSpriteIndex];	   	
		   stats = new ZombieStats();
		}
		trackSprite(activeSpriteIndex);
}


ZombieChaseManager::~ZombieChaseManager() {
	KILL_YOURSELF();
	delete mask;
	delete collisionMask;
}

ZombieChaseManager::ZombieChaseManager() : Manager(), 
	game(Game::getInstance()),  bgSurface(fact->makeSurface(bgSurfaceString)),
	background(fact->makeFrame(bgSurfaceString)), zombies(), people(), splats(), 
	splosions(), bullets(), activeSprite(NULL), activeSpriteIndex(0), 
	world(fact->getFrame(bgSurfaceString)), view(Viewport::getInstance()), 
   mask(NULL), collisionMask(NULL), stats(NULL), clouds(), playerType(1)
{
	loadFrames();
   initializeGame();   
   if(loadFlag)
		REBIRTH_YOURSELF();
   else
		BIRTH_YOURSELF();
   initializeClouds();	
   initializeMasks();
   amPlaying = true;
}

void ZombieChaseManager::drawAndUpdateMask() {
   mask->setX(activeSprite->getX() - 513 - 150);
   mask->setY(activeSprite->getY() - 301 - 150);
   mask->getFrame()->draw(static_cast<Sint16>(mask->getX() - view->getX()), 
                                             static_cast<Sint16>(mask->getY() - view->getY()));
   collisionMask->setX(activeSprite->getX() + activeSprite->getFrame()->getWidth() - (collisionMask->getFrame()->getWidth()/2));
   collisionMask->setY(activeSprite->getY() + activeSprite->getFrame()->getHeight()- (collisionMask->getFrame()->getHeight()/2));
   collisionMask->getFrame()->draw(static_cast<Sint16>(collisionMask->getX() - view->getX()), 
                                                          static_cast<Sint16>(collisionMask->getY() - view->getY()));
}
   
void ZombieChaseManager::trackSprite(const unsigned int i) {
	if(playerType == 0) {
		view->setObjectToTrack(people[i]);
	   if(!(people[i]->getTracked()))
		   people[i]->toggleTracked();		
   	people[i]->setXSpeed(0.0);
  		people[i]->setYSpeed(0.0);
	   activeSprite = people[i];
		activeSprite->setFrame(fact->getFrame(humanFaceSurfaceString));		
	}
	else {
	   view->setObjectToTrack(zombies[i]);
		if(!(zombies[i]->getTracked()))
	   	zombies[i]->toggleTracked();
	   zombies[i]->setXSpeed(0.0);
  		zombies[i]->setYSpeed(0.0);
	   activeSprite = zombies[i];   
	}
}

void ZombieChaseManager::makeBullet(int x, int y) { 	   
// 	(*sManager)[14];
   Vector2D mouse(static_cast<float>(x + view->getX()), 
                              static_cast<float>(y + view->getY()));
   Vector2D origins = activeSprite->getCoordinate();
   origins[0] += (activeSprite->getFrame()->getWidth() / 2);
   origins[1] += (activeSprite->getFrame()->getHeight() / 2);
   Vector2D shoot = mouse - origins;
   shoot.normalize();
   shoot *= game->getBulletSpeed();
   bullets.push_back(Bullet(origins, shoot, fact->getFrame(bulletSurfaceString)));
}

/*void ZombieChaseManager::drawZombieBar(const Uint32 color1, const Uint32 color2) {
    io->printMessageAt("Zombies: ", 120, 10);
    Draw_FillRect(screen, 220, 10, 10 * zombies.size(), 10, color1);
    Draw_Rect(screen, 220, 10, 10 * zombies.size(), 10, color2);

}   

void ZombieChaseManager::drawPeopleBar(const Uint32 color1, const Uint32 color2) {
    io->printMessageAt("People: ", 120, 40);
    Draw_FillRect(screen, 220, 40, 10 * people.size(), 10, color1);
    Draw_Rect(screen, 220, 40, 10 * people.size(), 10, color2);
}*/

void ZombieChaseManager::play() {
	
/*   const Uint32 BLUE
   const Uint32 BLACK = SDL_MapRGB(screen->format, 0, 0, 0);
   const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0x00, 0x00);*/
//   (*sManager)->startMusic(0);
   srand(time(NULL));
   SDL_Event event;
   Uint32 ticks, aiInterval = 500, shootInterval = 250;
   bool keyDown = false, mouseDown = false;

   while ( ! done ) {
      ticks = timer.getTicks(); 
		background.draw(0, 0);
      world.draw();   
      view->update(); 
      world.update();     
      
      stats->calculateScore();
     	zombiesEatingCheck();
     	if(timer.getTrackIntervalTicks() > aiInterval) {
     	   timer.setTrackIntervalTicks(0);
        	zombiesFindDinner();
        	peopleRunAway();
      }
      
      drawAndUpdateSprite(splats, ticks);
      drawAndUpdateSprite(splosions, ticks);
      drawAndUpdateSprite(people, ticks);
      drawAndUpdateSprite(zombies, ticks);                  
     	drawAndUpdateBullets(ticks); 	
     	drawAndUpdateMask();
     	clouds.update(ticks);
     	clouds.draw();
//      drawZombieBar(RED, BLACK);
//      drawPeopleBar(BLUE, BLACK);
      io->printMessageValueAt("FPS: ", timer.fps(), 10, 10);
      io->printMessageValueAt("Score: ", stats->getScore(), 10, 30);
      SDL_Flip(screen);
           
 		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT) {
         done = true;
         break;
	   }
	   if(event.type == SDL_MOUSEBUTTONUP)
	      mouseDown = false;
	   if(event.type == SDL_MOUSEBUTTONDOWN && mouseDown == false) {
	      if(playerType == 0) {
	         if(timer.getShootIntervalTicks() > shootInterval) {
	            timer.setShootIntervalTicks(0);
   	         makeBullet(event.motion.x, event.motion.y);
            }
	      }
	      mouseDown = true;
	   }
      if(event.type == SDL_KEYUP) keyDown = false;
		if(event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
               case SDLK_q:
               case SDLK_ESCAPE:
                        done = true;
                        break;
                        
               case SDLK_SPACE: {
                  if(keyDown == false) {
                     if(playerType == 1) {
                          zombies[activeSpriteIndex]->toggleTracked();
                          zombies[activeSpriteIndex]->setSpeed(zombies[activeSpriteIndex]->getInitSpeed());
                           activeSpriteIndex = (activeSpriteIndex + 1) % zombies.size();               
	                        trackSprite(activeSpriteIndex);
                  	}
                  	else if(playerType == 0) {
                          people[activeSpriteIndex]->toggleTracked();
                          people[activeSpriteIndex]->setSpeed(
                                                                 people[activeSpriteIndex]->getInitSpeed());
                          activeSpriteIndex = (activeSpriteIndex + 1) % people.size();	            	            	
                          trackSprite(activeSpriteIndex);
                    }
                  }
                  break;
               }
               case SDLK_h: {
                  if(keyDown == false) {
            	      timer.pause();	  
                     initializeGame();
                     timer.unpause();  
                     if(done == true)
                     	return;
                  }
                  break;
            	 }
            case SDLK_s: {
            	if(keyDown == false) {
            		saveSprite(people, "people", "chase");
            		saveSprite(zombies, "zombie", "chase");
            		saveSprite(splats, "splat", "chase");
            		saveSprite(splosions, "splosion", "chase");
            		saveStats(stats, "stat", "chase");
            		saveBullets(bullets, "bullet", "chase");            	
            		break;
            	}
            }
            case SDLK_l: {
            	if(keyDown == false) {
            		KILL_YOURSELF();
            		REBIRTH_YOURSELF();
            	}
            	break;
            }
            default: break;
          }
          if(event.key.keysym.sym == SDLK_UP) activeSprite->incrYSpeed(-1);
          if(event.key.keysym.sym == SDLK_DOWN) activeSprite->incrYSpeed(1);
          if(event.key.keysym.sym == SDLK_LEFT) activeSprite->incrXSpeed(-1);
          if(event.key.keysym.sym == SDLK_RIGHT) activeSprite->incrXSpeed(1); 
			 keyDown = true;
      }
      if(zombies.size() == 0 || people.size() == 0)
      	callEndGameScreen();
      }        
   }  

void ZombieChaseManager::handleEndGameText() {
	if(zombies.size() == 0) {
	   io->printMessageCenteredAt("Congratulations!", 240);
      io->printMessageCenteredAt("You have ended the zombie apocalypse!", 270);
      io->printMessageCenteredAt("The spoils and (remaining) women go to you!", 300);
   }
   else if(people.size() == 0) {
   	io->printMessageCenteredAt("Congratulations!", 240);
      io->printMessageCenteredAt("You have ended the human infestation of Earth!", 270);
      io->printMessageCenteredAt("You will spend an eternity starving and feeling the pain of your own decay", 300);
   }
}

void ZombieChaseManager::callEndGameScreen() {
     bool keyDown = false;
	   SDL_Event event;
		while(true) {
			background.draw(0, 0);
   	   world.draw();   
			handleEndGameText();
         SDL_Flip(screen);
   		SDL_PollEvent(&event);         
      	if(event.type == SDL_QUIT) { done = true; break; }
      	if(event.type == SDL_KEYUP) keyDown = false;
         if(event.type == SDL_KEYDOWN) {
            if(keyDown == false) {
               switch(event.key.keysym.sym) {
                  case SDLK_q:
                  case SDLK_ESCAPE:
                      done = true;
                      return;
                      break;
                  case SDLK_h:
                  	initializeGame ();
                   default:
                      done = true;
                      break;   
               }
            keyDown = true;
         }
      }
   }  
}

void ZombieChaseManager::initializeGame() {
      bool keyDown = false;
      bool mouseDown = false;
	   SDL_Event event;
	   float sx = view->getX() + 200, sy = view->getY();
	   int x, y;
		Sprite loadButton(sx, sy + 80, 0, 0, fact->getFrame(loadButtonSurfaceString));
		Sprite zombieButton(sx, sy + 160, 0, 0, fact->getFrame(zombieButtonSurfaceString));
		Sprite peopleButton(sx, sy + 240, 0, 0, fact->getFrame(humanButtonSurfaceString));
		Sprite helpButton(sx, sy + 320, 0, 0, fact->getFrame(helpButtonSurfaceString));
		Sprite returnButton(sx, sy + 400, 0, 0, fact->getFrame(returnButtonSurfaceString));
		while(true) {
			background.draw(0, 0);
   	   world.draw();   
   		loadButton.draw();
   		zombieButton.draw();
   		peopleButton.draw();
   		helpButton.draw();
   		returnButton.draw();
         SDL_Flip(screen);
   		SDL_PollEvent(&event);         
	      if(event.type == SDL_MOUSEBUTTONUP)
	         mouseDown = false;
   	   if(event.type == SDL_MOUSEBUTTONDOWN && mouseDown == false) {
	      	mouseDown = true;
	      	x = event.motion.x + static_cast<int>(view->getX());
	      	y = event.motion.y + static_cast<int>(view->getY());
	      	if(x > loadButton.getX() && x < loadButton.getX() + loadButton.getFrame()->getWidth()) {
	      		if(y > loadButton.getY() && y < loadButton.getY() + loadButton.getFrame()->getHeight()) {
	      			if(amPlaying) {
      					cout<<"Totally loading the game via click"<<endl;	      			
	      				KILL_YOURSELF();
	      				REBIRTH_YOURSELF();
	      			}	
	      			else
	      		   	loadFlag = true;
	      		   return;
	      		}
	      		else if(y > zombieButton.getY() && y < zombieButton.getY() + zombieButton.getFrame()->getHeight()) {
						playerType = 1;	      		
						if(amPlaying) {
							KILL_YOURSELF();
							BIRTH_YOURSELF();
						}
						else
							loadFlag = false;
						return;
	      		}
	      		else if(y > peopleButton.getY() && y < peopleButton.getY() + peopleButton.getFrame()->getHeight()) {
	      		   playerType = 0;
						if(amPlaying) {
							KILL_YOURSELF();
							BIRTH_YOURSELF();
						}	      		   
						else
							loadFlag = false;
	      		   return;
	      		}
	      		else if(y > helpButton.getY() && y < helpButton.getY() + helpButton.getFrame()->getHeight()) {
	      			callHelpScreen();
	      		}
	      		else if(y > returnButton.getY() && y < returnButton.getY() + returnButton.getFrame() ->getHeight())
	      			if(!amPlaying)
	      				done = true;
	      			return;
	      	}
		   }
      	if(event.type == SDL_QUIT) { done = true; break; }
      	if(event.type == SDL_KEYUP) keyDown = false;
         if(event.type == SDL_KEYDOWN) {
               switch(event.key.keysym.sym) {
                  case SDLK_q:
                  case SDLK_ESCAPE:
                      done = true;
                      return;
                      break;
               	case SDLK_p:
               		if(keyDown == false) {
		      			   playerType = 0;
								if(amPlaying) {
									KILL_YOURSELF();
									BIRTH_YOURSELF();
								}
								else
									loadFlag = false; 		   
            			    return;
            			}
            			break;
            		case SDLK_z:
            			if(keyDown == false) {
		      		   	playerType = 1;
								if(amPlaying) {
									KILL_YOURSELF();
									BIRTH_YOURSELF();
								}	      	
								else
									loadFlag = false;	   
	      			   	return;
	      			  	}
	      			  	break;
	      		   case SDLK_l:
	      		   	if(keyDown == false) {
		      				if(amPlaying) {
		      					cout<<"Totally loading the via button game"<<endl;
	   	   					KILL_YOURSELF();
	      						REBIRTH_YOURSELF();
	      					}
	      					else
	      						loadFlag = true;
            		 		return;
            		 	}
            		 	break;
            		default: break;            		 	
                  case SDLK_h:
                  	if(keyDown == false)
            		    callHelpScreen();
            		   break;
               }
            keyDown = true;
      }
   }  
}

void ZombieChaseManager::callHelpScreen() {
   SDL_Event event;
   bool keyDown = false, mouseDown = false;
   float sx = view->getX() + 200, sy = view->getY();
   Sprite returnButton(sx, sy + 400, 0, 0, fact->getFrame(returnButtonSurfaceString));
	Uint32 x, y;
	while(true) {
		background.draw(0, 0);
 	   world.draw();   
 	   returnButton.draw();
      io->printMessageCenteredAt("Welcome to the Zombie Apocalypse!", 70);
      io->printMessageCenteredAt("In this game, you play as the humans, ", 95);
      io->printMessageCenteredAt("hoping to survive against the zombie onslaught!", 
                                                      120);
      io->printMessageCenteredAt("Or play as the zombies in an attempt", 145);
      io->printMessageCenteredAt("to satisfy your insatiable craving for BRRRAAAAIIINNNSSSSS!", 170);

      io->printMessageCenteredAt("Humans: Try to shoot zombies to stop the infection", 220);
      io->printMessageCenteredAt("Zombies: Track down your next meal and feast", 245);
      io->printMessageCenteredAt("Controls", 270);
      io->printMessageAt("H - Opens / Closes Help Menu", 320, 340);
      io->printMessageAt("Arrow Keys - Movement", 0, 310);
      io->printMessageAt("Mouse Cursor - Aims", 0, 335);
      io->printMessageAt("Left Mouse Click - Fire Gun (Human Only)", 320, 310);
      io->printMessageAt("Escape - Exits Game", 320, 370);
      SDL_Flip(screen);
		SDL_PollEvent(&event);
		if(event.type == SDL_MOUSEBUTTONUP) mouseDown = false;
		if(event.type == SDL_MOUSEBUTTONDOWN) {
		  	x = event.motion.x + static_cast<int>(view->getX());
		  	y = event.motion.y + static_cast<int>(view->getY());   
			if(x > returnButton.getX() && x < returnButton.getX() + returnButton.getFrame()->getWidth()) {
				if(y > returnButton.getY() && y < returnButton.getY() + returnButton.getFrame()->getHeight()) {
	      			if(!amPlaying)
	      				done = true;
	      			return;
	   	  	}
	     		mouseDown = true;
	   	}
	   }
     	if(event.type == SDL_QUIT)  { done = true; break; }
    	if(event.type == SDL_KEYUP) keyDown = false;
      if(event.type == SDL_KEYDOWN) {
         if(keyDown == false) {
            switch(event.key.keysym.sym) {
               case SDLK_q:
               case SDLK_ESCAPE:
                   done = true;
                   return;
               case SDLK_h: return;
               default: 
               	break;
           }
           keyDown = true;
   	   }
      }	
  }
}  

void ZombieChaseManager::zombiesEatingCheck() {
   for(unsigned int i = 0; i < zombies.size(); ++i)  {   
      for(unsigned int j = 0; j < people.size(); ++j) {      
         if((*collisions)[0]->execute(*(zombies[i]), *(people[j]))) {
            zombiesEatPeople(j);
         }
      }
   }
}   

void ZombieChaseManager::zombiesFindDinner() {
   float distance, minDistance = 2000;
   int selected = -1;
   for(unsigned int i = 0; i < zombies.size(); ++i) {
      if(!(zombies[i]->getTracked())) {
         for(unsigned int j = 0; j < people.size(); ++j) { 
            distance = (*collisions)[0]->distance(*(zombies[i]), *(people[j]));
            if(distance < minDistance) {
               minDistance = distance;
               selected = j;
          }
        }
      if(selected > -1) zombies[i]->setSpeed((*flee)[zombies[i]->
                                 getFleeStrategyCode()]->flee(*(zombies[i]), *(people[selected])));
     }
     minDistance = 2000;
   }
}

void ZombieChaseManager::zombiesEatPeople(int i) {
	vector<Sprite *>::iterator it = people.begin() + i;
   zombies.push_back(new Zombie(people[i]->getX(), people[i]->getY(), 
                                    static_cast<float>(rand() % 30 -15),  
                                    static_cast<float>(rand() % 30 -15), 
                                    fact->getFrame(zombieFaceSurfaceString)));
   splosions.push_back(new Explosion(*(people[i]), fact->getFrameKey(people[i]->getFrame())));
   makeSplats(*people[i]);
   stats->setPeopleEaten(stats->getPeopleEaten() + 1);
   if(people[i]->getTracked()) {
      stats->setTimesDied(stats->getTimesDied() + 1);
      activeSpriteIndex = (activeSpriteIndex + 1) % people.size();	            	            	
      trackSprite(activeSpriteIndex);
   }   
	delete *(it);
   people.erase(people.begin() + i);
//   (*sManager)[4 + (rand() % 9)];   
}

void ZombieChaseManager::peopleRunAway() {
   float distance, minDistance = 2000;
   int selected = -1;
   for(unsigned int i = 0; i < people.size(); ++i) { 
      if(!(people[i]->getTracked())) {
	   for(unsigned int j = 0; j < zombies.size(); ++j) {
            distance = (*collisions)[0]->distance(*(zombies[j]), *(people[i]));
            if(distance < minDistance) {
               minDistance = distance;
               selected = j;
          }
        }
        if(selected > -1 && minDistance > 96 && minDistance < 192) {
        		people[i]->setSpeed((*flee)[people[i]->getFleeStrategyCode()]->flee(
                                            *(zombies[selected]), *(people[i])) * 1.5);        		            
        		people[i]->setFrame(fact->getFrame(scaredFaceSurfaceString));
        	}
        	else if(selected > -1 && minDistance < 96){

        		people[i]->setSpeed((*flee)[people[i]->getFleeStrategyCode()]->flee(
        		                                *(people[i]), *(zombies[selected])) * 1.7);
        		people[i]->setFrame(fact->getFrame(freakedFaceSurfaceString));	
        		
         }
        	else if (selected > -1 && people[i]->getFrame() != \
        	            fact->getFrame(humanFaceSurfaceString)) {
        		people[i]->setFrame(fact->getFrame(humanFaceSurfaceString));	
        		people[i]->setSpeed(people[i]->getInitSpeed());
         }
        	minDistance = 2000;
	   }
	}
}
        
void ZombieChaseManager::loadFrames() {
   fact->makeSprite(game->getData(zombieFaceSurfaceString));
   fact->makeSprite(game->getData(humanFaceSurfaceString));
   fact->makeSprite(game->getData(bloodSplatSurfaceString));
   fact->makeSprite(game->getData(bloodSplat2SurfaceString));
  	fact->makeSprite(game->getData(bloodSplat3SurfaceString));
   fact->makeSprite(game->getData(bloodSplat4SurfaceString));
   fact->makeSprite(game->getData(scaredFaceSurfaceString));
   fact->makeSprite(game->getData(freakedFaceSurfaceString));
   fact->makeSprite(game->getData(bulletSurfaceString));
   fact->makeSprite(game->getData(loadButtonSurfaceString)); 
   fact->makeSprite(game->getData(humanButtonSurfaceString));  
   fact->makeSprite(game->getData(zombieButtonSurfaceString));   
   fact->makeSprite(game->getData(helpButtonSurfaceString));
   fact->makeSprite(game->getData(returnButtonSurfaceString));
}

void ZombieChaseManager::initializeMasks() {
   SDL_SetAlpha(fact->makeSurface("images/mask.bmp"), SDL_SRCALPHA, 200);
   mask = new Sprite(activeSprite->getX() - 513, activeSprite->getY() - 301, 0, 0, 
                                   fact->makeFrame("images/mask.bmp")); 			   
   SDL_SetAlpha(fact->makeSurface("images/collisionMask.bmp"), SDL_SRCALPHA, 0);                                   
   collisionMask = new Sprite(0, 0, 0, 0, fact->makeFrame("images/collisionMask.bmp"));
   collisionMask->setX(activeSprite->getX()  + (activeSprite->getFrame()->getWidth()/2) - (collisionMask->getFrame()->getWidth()/2));
   collisionMask->setY(activeSprite->getY()  + (activeSprite->getFrame()->getHeight()/2) - (collisionMask->getFrame()->getHeight()/2));   
}                                  

void ZombieChaseManager::initializeZombies() {
   for(unsigned int i = 0; i < game->getZombieCount(); ++i) {
      zombies.push_back(new Zombie(
                                       static_cast<float>(game->getWorldWidth() / (i+1)), 
                                       static_cast<float>(game->getWorldHeight() / (i+1)),  
                                       static_cast<float>(rand() % 50 -25),  
                                       static_cast<float>(rand() % 50 -25), 
                                       fact->getFrame(zombieFaceSurfaceString)));
      zombies[i]->setFleeStrategyCode(2);
   }
}

void ZombieChaseManager::initializePeople() {
   for(unsigned int i = 0; i < game->getPeopleCount(); ++i) {
      people.push_back(new People(static_cast<float>(rand() % 1280), 
                                                        static_cast<float>(rand() % 960), 
                                                        static_cast<float>(rand() % 40 - 20), 
                                                        static_cast<float>(rand ()% 40 - 20), 
                                                        fact->getFrame(humanFaceSurfaceString)));
      people[i]->setFleeStrategyCode(rand() % 2);
   }
}

void ZombieChaseManager::initializeClouds() {
	SDL_SetAlpha(fact->makeSurface(cloud1SurfaceString), SDL_SRCALPHA, 220);
	SDL_SetAlpha(fact->makeSurface(cloud2SurfaceString), SDL_SRCALPHA, 220);
	SDL_SetAlpha(fact->makeSurface(cloud3SurfaceString), SDL_SRCALPHA, 220);
	SDL_SetAlpha(fact->makeSurface(cloud4SurfaceString), SDL_SRCALPHA, 220);		
   for(int i = 0; i < 4; i++) {
      clouds.addSprite(cloud1SurfaceString);
      clouds.addSprite(cloud2SurfaceString);   
      clouds.addSprite(cloud3SurfaceString);
      clouds.addSprite(cloud4SurfaceString);
   }
}   

void ZombieChaseManager::drawAndUpdateSprite(vector<Sprite *> &v, Uint32 ticks) {
	for(unsigned int i = 0; i < v.size(); ++i) {
		v[i]->update(ticks);
		if((*collisions)[1]->execute(*(collisionMask), *(v[i])))		
			v[i]->draw();
	}
}

void ZombieChaseManager::drawAndUpdateBullets(Uint32 ticks) {
   cullBullets();
   bool hitFlag = false;
   for(unsigned int i = 0; i < bullets.size(); ++i) {   
      for(unsigned int j = 0; j < zombies.size(); ++j) {
         if((*collisions)[0]->execute(bullets[i], *(zombies[j]))) {
//         	(*sManager)[(rand() % 4)];
				bulletsExplodeSprite(*(zombies[j]));
				delete zombies[j];
				zombies.erase(zombies.begin() + j);
            bullets.erase(bullets.begin() + i);            
            stats->setZombiesKilled(stats->getZombiesKilled() + 1);
            hitFlag = true;
            break;
         }
      }
      for(unsigned int k = 0; k < people.size(); ++k) {
      	if(hitFlag == true)
      		break;
         if((*collisions)[0]->execute(bullets[i], *(people[k])) && 
         														people[k]->getTracked() == false) {
//		      (*sManager)[4 + (rand() % 9)];
//            bulletsExplodePeople(k);
				bulletsExplodeSprite(*(people[k]));
				delete people[k];            
				people.erase(people.begin() + k);
            bullets.erase(bullets.begin() + i);
            stats->setPeopleShot(stats->getPeopleShot() + 1);
            hitFlag = true;
         }
      }   
      hitFlag = false;     
  }
  for(unsigned int i = 0; i < bullets.size(); ++i) {
     bullets[i].update(ticks);
     bullets[i].draw();
  }
}

void ZombieChaseManager::bulletsExplodeSprite(Sprite &s) {
	splosions.push_back(new Explosion(s, fact->getFrameKey(s.getFrame())));
   makeSplats(s);	
}
/*
void ZombieChaseManager::bulletsExplodeZombies(const unsigned int i) {
   splosions.push_back(new Explosion(*(zombies[i]), zombieFaceSurfaceString));
   makeSplats(*(zombies[i]));
 	vector<Sprite *>::iterator it = zombies.begin() + i;
 	delete *it;
 	zombies.erase(zombies.begin() + i);
}

void ZombieChaseManager::bulletsExplodePeople(const unsigned int i) {
   splosions.push_back(new Explosion(*(people[i]), fact->getFrameKey(people[i]->getFrame())));
   makeSplats(*(people[i]));
 	vector<Sprite *>::iterator it = people.begin() + i;
   delete *it;
 	people.erase(people.begin() + i);
}
   */
void ZombieChaseManager::makeSplats(Sprite& s) {
   int temp = rand() % 4;
   if(temp == 0)
	   splats.push_back(new Sprite(s.getX(), s.getY(), 0.0, 0.0, 0.0, 0.0, false, fact->getFrame(bloodSplatSurfaceString)));
	else if(temp == 1)
	   splats.push_back(new Sprite(s.getX(), s.getY(), 0.0, 0.0, 0.0, 0.0, false, fact->getFrame(bloodSplat2SurfaceString)));	
	else if(temp == 2)
	   splats.push_back(new Sprite(s.getX(), s.getY(), 0.0, 0.0, 0.0, 0.0, false, fact->getFrame(bloodSplat3SurfaceString)));	
	else if(temp == 3) 
	   splats.push_back(new Sprite(s.getX(), s.getY(), 0.0, 0.0, 0.0, 0.0, false, fact->getFrame(bloodSplat4SurfaceString)));	
}

void ZombieChaseManager::cullBullets() {
   vector<Bullet>::iterator bulletIterator = bullets.begin(); 
   for(unsigned int i = 0; i < bullets.size(); ++i) {
      if ( bullets[i].getDistance() >= game->getMaxBulletDistance())
         bullets.erase(bullets.begin() + i);
   }
}

void ZombieChaseManager::findTracked() {
	bool foundTracked = false;
	for(unsigned int i = 0; i < zombies.size(); ++i) {
		if(zombies[i]->getTracked()) {
			cout<<"Found a zombie to be tracked"<<endl;
			playerType = 1;
			activeSpriteIndex = i;
			trackSprite(activeSpriteIndex);			
			activeSprite = zombies[activeSpriteIndex];
			stats = new ZombieStats;
			foundTracked = true;
		}
	}
	if(!foundTracked) {
		for(unsigned int i = 0; i < people.size(); ++i) {
			if(people[i]->getTracked()) {
				cout<<"Found a playet to be tracked"<<endl;			
				playerType = 0;
				activeSpriteIndex = i;
				trackSprite(activeSpriteIndex);
				activeSprite = people[activeSpriteIndex];
				stats = new PlayerStats;
				foundTracked = true;
			}
		}
	}
	if(activeSprite == false)
		cout<<"Was unable to find a trackable source!"<<endl;	
}
