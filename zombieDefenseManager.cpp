#include "zombieDefenseManager.h"
using std::cout; 
using std::string;
using std::vector;
using std::endl; 

const string bgSurfaceString ("images/bground.bmp");
const string zombieFaceSurfaceString("images/zombieFace.bmp");
const string humanFaceSurfaceString ("images/humanFace.bmp");
const string bloodSplatSurfaceString ("images/bloodsplat.bmp");
const string bloodSplat2SurfaceString ("images/bloodsplat2.bmp");
const string bloodSplat3SurfaceString ("images/bloodsplat3.bmp");
const string bloodSplat4SurfaceString ("images/bloodsplat4.bmp");
const string femaleFaceSurfaceString ("images/femaleFace.bmp");
const string bulletSurfaceString ("images/bullet.bmp");
const string loadButtonSurfaceString("images/loadButton.bmp");
const string zombieButtonSurfaceString("images/zombieButton.bmp");
const string helpButtonSurfaceString("images/helpButton.bmp");
const string returnButtonSurfaceString("images/returnButton.bmp");

ZombieDefenseManager::ZombieDefenseManager() : Manager(), 
   game(Game::getInstance()),  bgSurface(fact->makeSurface(bgSurfaceString)),
	background(fact->makeFrame(bgSurfaceString)), lastFemaleOnEarth(NULL),
   zombies(), people(), splats(), splosions(), bullets(), world(fact->getFrame(bgSurfaceString)),
   loseCondition(false), view(Viewport::getInstance()), stats(new PlayerStats()) {
	loadFrames();   
	view->setX(0.0);
	view->setY(0.0);
	initializeGame();
}

void ZombieDefenseManager::KILL_YOURSELF() {
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

void ZombieDefenseManager::REBIRTH_YOURSELF() {
   	loadSprite(zombies, "zombie", "defense");
   	loadSprite(people, "people", "defense");
   	loadStats(stats, "stat", "defense");
   	loadSprite(splats, "splat", "defense");   	
   	loadBullets(bullets, "bullet", "defense");
   	loadExplosion(splosions, "splosion", "defense");
   	lastFemaleOnEarth = new People(5, 240, 0, 0, fact->getFrame(femaleFaceSurfaceString));   	   	
}

void ZombieDefenseManager::BIRTH_YOURSELF() {
	lastFemaleOnEarth = new People(5, 240, 0, 0, fact->getFrame(femaleFaceSurfaceString));
	view->setX(0.0);
	view->setY(0.0);
	placeInitialHumans();
	placeInitialZombies();
}

ZombieDefenseManager::~ZombieDefenseManager() {
	KILL_YOURSELF();
	delete lastFemaleOnEarth;
}

void ZombieDefenseManager::placeInitialHumans() {
   unsigned int i = 0;
   SDL_Event event;
   bool mouseDown = false, keyDown = false;
   float x, y;
   string hleft = "Humans left to be placed: ";
   while(i < game->getInitialHumans()) {
   	background.draw(0, 0);
   	world.draw();
   	drawAndUpdateSprite(people, 0);
   	io->printMessageCenteredAt("Place your humans to defend the objective!", 30);
   	io->printMessageValueAt(hleft, static_cast<int>(game->getInitialHumans() - i), 180, 60);
   	SDL_Flip(screen);
      SDL_PollEvent(&event);
		
		if(event.type == SDL_QUIT) {
         done = true;
         break;
	   }      
	   
      if(event.type == SDL_MOUSEBUTTONDOWN && mouseDown == false) {
         mouseDown = true;
         x = event.motion.x;
         y = event.motion.y;
         people.push_back(new People(x, y, 0, 0, fact->getFrame(humanFaceSurfaceString)));
         i++;
         mouseDown = true;
      }
      
      if(event.type == SDL_MOUSEBUTTONUP) mouseDown = false;
      if(event.type == SDL_KEYUP) keyDown = false;
      
      if(event.type == SDL_KEYDOWN) {
         if(keyDown == false) {
          switch (event.key.keysym.sym) {
               case SDLK_q:
               case SDLK_ESCAPE:
                        done = true;
                        break;
               case SDLK_h: {
                  if(keyDown == false) {
            	      timer.pause();	  
                     initializeGame();
                     timer.unpause();  
                     if(done == true)
                     	return;
                  }
                  break;
                default:
                	break;
               }
            }
			keyDown = true;
         }
      }
   }
}

void ZombieDefenseManager::placeInitialZombies() {
	float speedFactor = people.size()/game->getInitialHumans();
	if(speedFactor < 1)
		speedFactor = 1;
	while(zombies.size() < game->getInitialZombies()) {
		zombies.push_back(new Zombie(static_cast<float>(rand()% 240) + 640, static_cast<float>(rand()% 240) + 120, static_cast<float>(rand() % 30 + 10) * -1 * speedFactor,  0, fact->getFrame(zombieFaceSurfaceString)));
	}
}
         
void ZombieDefenseManager::handleEndGameText() {
   	io->printMessageCenteredAt("GAME OVER!", 240);
      io->printMessageCenteredAt("The zombies have found and destroyed The Last Woman On Earth!", 270);
      io->printMessageCenteredAt("While you made a valiant stand, there's just no point in living", 300);
}

void ZombieDefenseManager::callEndGameScreen() {
      bool keyDown = false;
	   SDL_Event event;
	   world.draw();
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
                  	initializeGame();
                   default:
                      done = true;
                      break;   
               }
            keyDown = true;
         }
      }
   }  
}


/********************END OF INITIALIZATION FUNCTIONS **************************/

/*************************BULLET FUNCTIONS************************************/

void ZombieDefenseManager::cullBullets() {
   vector<Bullet>::iterator bulletIterator = bullets.begin(); 
   for(unsigned int i = 0; i < bullets.size(); ++i) {
      if ( bullets[i].getDistance() >= game->getMaxBulletDistance())
         bullets.erase(bullets.begin() + i);
   }
}

void ZombieDefenseManager::drawAndUpdateBullets(Uint32 ticks) {
   cullBullets();
   bool hitFlag = false;
   for(unsigned int i = 0; i < bullets.size(); ++i) {   
      for(unsigned int j = 0; j < zombies.size(); ++j) {
           if((*collisions)[0]->execute(bullets[i], *(zombies[j]))) {
            bulletsExplodeSprite(*(zombies[j]));
            delete zombies[j];
            zombies.erase(zombies.begin() + j);
            bullets.erase(bullets.begin() + i);            
            stats->setZombiesKilled(stats->getZombiesKilled() + 1);
            hitFlag = true;
            break;
         }
      }
  }
  for(unsigned int i = 0; i < bullets.size(); ++i) {
     bullets[i].update(ticks);
     bullets[i].draw();
  }
}

void ZombieDefenseManager::bulletsExplodeSprite(Sprite &s) {
	splosions.push_back(new Explosion(s, fact->getFrameKey(s.getFrame())));
   makeSplats(s);	
}

/*************************ENF OF BULLET FUNCTIONS*****************************/

void ZombieDefenseManager::zombiesEatingCheck() {
   for(unsigned int i = 0; i < zombies.size(); ++i)  {   
      for(unsigned int j = 0; j < people.size(); ++j) {      
         if((*collisions)[0]->execute(*(zombies[i]), *(people[j]))) {
            zombiesEatPeople(j);
         }
      }
		if((*collisions)[0]->execute(*(zombies[i]), *lastFemaleOnEarth)) {
			loseCondition = true;
			splosions.push_back(new Explosion(*lastFemaleOnEarth, fact->getFrameKey(lastFemaleOnEarth->getFrame())));
		}
   }
}   

void ZombieDefenseManager::zombiesEatPeople(int i) {
	vector<Sprite *>::iterator it = people.begin() + i;
   zombies.push_back(new Zombie(people[i]->getX(), people[i]->getY(), 
                                    static_cast<float>(rand() % 30 -15),  
                                    static_cast<float>(rand() % 30 -15), 
                                    fact->getFrame(zombieFaceSurfaceString)));
   splosions.push_back(new Explosion(*(people[i]), fact->getFrameKey(people[i]->getFrame())));
   makeSplats(*people[i]);
   stats->setPeopleEaten(stats->getPeopleEaten() + 1);
   delete *(it);
   people.erase(people.begin() + i);
}

void ZombieDefenseManager::makeSplats(Sprite& s) {
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

void ZombieDefenseManager::initializeGame() { 
      bool keyDown = false;
      bool mouseDown = false;
	   SDL_Event event;
	   float sx = view->getX() + 200, sy = view->getY();
	   int x, y;
		Sprite loadButton(sx, sy + 80, 0, 0, fact->getFrame(loadButtonSurfaceString));
		Sprite zombieButton(sx, sy + 160, 0, 0, fact->getFrame(zombieButtonSurfaceString));
		Sprite helpButton(sx, sy + 240, 0, 0, fact->getFrame(helpButtonSurfaceString));
		Sprite returnButton(sx, sy + 320, 0, 0, fact->getFrame(returnButtonSurfaceString));
		while(true) {
			background.draw(0, 0);
   	   world.draw();   

   		loadButton.draw();
   		zombieButton.draw();
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
	      				KILL_YOURSELF();
	      				REBIRTH_YOURSELF();
	      			}	
	      			else
	      		   	loadFlag = true;
	      		   return;
	      		}
	      		else if(y > zombieButton.getY() && y < zombieButton.getY() + zombieButton.getFrame()->getHeight()) {
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
            		case SDLK_z:
            			if(keyDown == false) {
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

void ZombieDefenseManager::loadFrames() { 
   fact->makeSprite(game->getData(zombieFaceSurfaceString));
   fact->makeSprite(game->getData(humanFaceSurfaceString));
   fact->makeSprite(game->getData(bloodSplatSurfaceString));
   fact->makeSprite(game->getData(bloodSplat2SurfaceString));
  	fact->makeSprite(game->getData(bloodSplat3SurfaceString));
   fact->makeSprite(game->getData(bloodSplat4SurfaceString));
   fact->makeSprite(game->getData(bulletSurfaceString));   
   fact->makeSprite(game->getData(femaleFaceSurfaceString));
   fact->makeSprite(game->getData(loadButtonSurfaceString)); 
   fact->makeSprite(game->getData(zombieButtonSurfaceString));   
   fact->makeSprite(game->getData(helpButtonSurfaceString));
   fact->makeSprite(game->getData(returnButtonSurfaceString));
   fact->printFrameMap();
}
		
void ZombieDefenseManager::play() { 
   Uint32 ticks;
   Uint32 trackInterval = 500, shootInterval = 1500;
   SDL_Event event;
   bool keyDown = false, mouseDown = false;
   if(!done) {
   	if(loadFlag)
			REBIRTH_YOURSELF();
		else
			BIRTH_YOURSELF();	
		amPlaying = true;
	}
   world.draw();
   timer.getTicks();
	int totalHumans = people.size();
   cout<<"Just wanted to let you know... I love you"<<endl;
   cout<<"totalHumans = "<<totalHumans<<endl;
   cout<<"initialHumans = "<<game->getInitialHumans()<<endl;	
   while(!done) {
   	placeInitialZombies();
   	zombiesEatingCheck();
      ticks = timer.getTicks();
      if(timer.getTrackIntervalTicks() > trackInterval)
      	zombiesChase();
      if(timer.getShootIntervalTicks() > shootInterval) {
         timer.setShootIntervalTicks(0);
      	peopleShoot();
      }
      world.draw();

      lastFemaleOnEarth->draw();
      drawAndUpdateSprite(splats, ticks);
      drawAndUpdateSprite(splosions, ticks);
      drawAndUpdateSprite(people, ticks);
	   drawAndUpdateSprite(zombies, ticks);
      drawAndUpdateBullets(ticks);
      stats->calculateScore();
      io->printMessageValueAt("FPS: ", timer.fps(), 10, 10);
      io->printMessageValueAt("Score: ", stats->getScore(), 10, 30);      
      io->printMessageValueAt("Humans left to be placed: ", static_cast<int>(game->getInitialHumans() + (stats->getScore() / 1000) - totalHumans), 140, 30);
      SDL_Flip(screen);
  		SDL_PollEvent(&event);
  		         
     	if(event.type == SDL_QUIT) { done = true; break; }
     	if(event.type == SDL_MOUSEBUTTONUP) mouseDown = false;
     	if(event.type == SDL_MOUSEBUTTONDOWN) {
     		if(mouseDown == false) {
	      	if(totalHumans < static_cast<int>(game->getInitialHumans() + (stats->getScore() / 1000))) {
   	  	      people.push_back(new People(event.motion.x, event.motion.y, 0, 0, fact->getFrame(humanFaceSurfaceString)));
     		      totalHumans++;
        		   mouseDown = true;
        		}
     		}
     	}
      if(event.type == SDL_KEYUP) keyDown = false;
      if(event.type == SDL_KEYDOWN) {
         if(keyDown == false) {
            switch(event.key.keysym.sym) {
               case SDLK_q:
               case SDLK_ESCAPE:
                  done = true;
                  break;
               case SDLK_h:
               	timer.pause();
                  initializeGame();
                  timer.unpause();
                  break;
                case SDLK_s:
            		saveSprite(people, "people", "defense");
            		saveSprite(zombies, "zombie", "defense");
            		saveSprite(splats, "splat", "defense");
            		saveSprite(splosions, "splosion", "defense");
            		saveStats(stats, "stat", "defense");
            		saveBullets(bullets, "bullet", "defense");            	
                default:
                  break;   
            	}
            	keyDown = true;
         	}
      	}
	   	if(people.size() == 0 || loseCondition == true)
   		{
   			done = true;
   			callEndGameScreen();
	   	}      	
   }	  
}

void ZombieDefenseManager::callHelpScreen() {
   SDL_Event event;
   bool keyDown = false, mouseDown = false;
   float sx = view->getX() + 200, sy = view->getY();
   Sprite returnButton(sx, sy + 400, 0, 0, fact->getFrame(returnButtonSurfaceString));
	Uint32 x, y;   
	while(true) {
		background.draw(0, 0);
 	   world.draw();   
      io->printMessageCenteredAt("Welcome to the Zombie Defense!", 70);
      io->printMessageCenteredAt("Place your Humans and Protect THE LAST WOMAN ON EARTH! ", 95);
      io->printMessageCenteredAt("Try to Survive Until Help Comes!", 115);
		
		io->printMessageCenteredAt("Additional humans awarded every 1000 Points", 240);
		io->printMessageCenteredAt("Beware, as the zombies get hungry, they also get faster", 270);
		
      io->printMessageCenteredAt("Controls", 300);
      io->printMessageCenteredAt("H - Opens / Closes Menu", 330);
      io->printMessageCenteredAt("Left Mouse Click - Place Additional Humans", 360);
      io->printMessageCenteredAt("Escape - Return to main menu", 390);
      SDL_Flip(screen);
		SDL_PollEvent(&event);
     	if(event.type == SDL_QUIT)  { done = true; break; }
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
    	if(event.type == SDL_KEYUP) keyDown = false;
      if(event.type == SDL_KEYDOWN) {
         if(keyDown == false) {
            switch(event.key.keysym.sym) {
               case SDLK_q:
               case SDLK_ESCAPE:
                   done = true;
                   return;
               case SDLK_h: 
               	return;
               default: 
               	break;
           }
           keyDown = true;
   	   }
      }	
  }
}  

void ZombieDefenseManager::zombiesChase() {

}

void ZombieDefenseManager::peopleShoot() {
	float distance, minDistance = 2000;
	int selected;
	for(unsigned int i = 0; i < people.size(); ++i) {
		for(unsigned int j = 0; j < zombies.size(); ++j) {
            distance = (*collisions)[0]->distance(*(zombies[j]), *(people[i]));
            if(distance < minDistance) {
               minDistance = distance;
               selected = j;
          }
       }
       if(minDistance < game->getMaxBulletDistance())
	       makeBullet(*(people[i]), *(zombies[selected]));
	    minDistance = 2000;
	}       
}

void ZombieDefenseManager::makeBullet(const Sprite& shooter, const Sprite& target) { 	   
   Vector2D origins = shooter.getCoordinate();
   origins[0] += (shooter.getFrame()->getWidth() / 2);
   origins[1] += (shooter.getFrame()->getHeight() / 2);
   float radius = shooter.getFrame()->getWidth() / 2 + shooter.getFrame()->getHeight() / 2;
   Vector2D shoot = target.getCoordinate() - origins;
   shoot.normalize();
   origins += radius * shoot;
   bullets.push_back(Bullet(origins, shoot * game->getBulletSpeed(), fact->getFrame(bulletSurfaceString)));
}

void ZombieDefenseManager::drawAndUpdateZombies(Uint32 ticks) {
	for(unsigned int i = 0; i < zombies.size(); ++i) {
		zombies[i]->update(ticks);
		zombies[i]->draw();
	}
}		
