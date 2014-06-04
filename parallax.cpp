#include "parallax.h"
#include "factory.h"
#include <iostream>

using std::cout; using std::endl;


void Parallax::addSprite(const string& s) {
   parallaxObjects.push_back(Sprite(
                              static_cast<float>(rand() * (parallaxObjects.size() + 2) / (parallaxObjects.size() + 1)% Game::getInstance()->getWorldWidth()),
                              static_cast<float>(rand() * (parallaxObjects.size() + 2) / (parallaxObjects.size() + 1) % Game::getInstance()->getWorldHeight()),
                              static_cast<float>(rand() % 8 * 2 + 8), 0, 
                              Factory::getInstance()->makeFrame(s)));
}

void Parallax::update(Uint32 ticks) {
   float spX, incrX, spY, incrY;
   int frameWidth, frameHeight;
   int worldWidth = Game::getInstance()->getWorldWidth(), 
         worldHeight = Game::getInstance()->getWorldHeight();
   for(unsigned int i = 0; i < parallaxObjects.size(); ++i) {
   spY = parallaxObjects[i].getYSpeed();
   incrY= spY * static_cast<float>(ticks) * 0.001;
   parallaxObjects[i].setY(parallaxObjects[i].getY() + incrY);

   frameHeight = parallaxObjects[i].getFrame()->getHeight();

   if(parallaxObjects[i].getY() < 0 - frameHeight)
      parallaxObjects[i].setY(worldHeight);
  else if(parallaxObjects[i].getY() > worldHeight)
      parallaxObjects[i].setY(0 - frameHeight);
   
   spX = parallaxObjects[i].getXSpeed();
   incrX = spX * static_cast<float>(ticks) * 0.001;
   parallaxObjects[i].setX(parallaxObjects[i].getX() + incrX);
   
   frameWidth = parallaxObjects[i].getFrame()->getWidth();
   
   if(parallaxObjects[i].getX() < 0 - frameWidth)
      parallaxObjects[i].setX(worldWidth);
   else if(parallaxObjects[i].getX() > worldWidth)
      parallaxObjects[i].setX(0 - frameWidth);
   }
}

void Parallax::draw() {
   for(unsigned int i = 0; i < parallaxObjects.size(); ++i) {
      parallaxObjects[i].draw();
   }
}                             
