#include "viewport.h"
#include "sprite.h"

//#include "game.h"


  Viewport::Viewport() : viewX(0), viewY(0), objWidth(0), objHeight(0), objectToTrack(NULL),
  							 viewWidth(Game::getInstance()->getViewWidth()),
							 viewHeight(Game::getInstance()->getViewHeight()),
							 worldWidth(Game::getInstance()->getWorldWidth()),							 
							 worldHeight(Game::getInstance()->getWorldHeight()) {}

Viewport* Viewport::getInstance() {
  if (!instance) {
    instance = new Viewport;
  }
  return instance;
}

void Viewport::setObjectToTrack(const Sprite *obj) { 
  objectToTrack = obj; 
  objWidth = objectToTrack->getFrame()->getWidth();
  objHeight = objectToTrack->getFrame()->getHeight();
  Viewport::update();
}

void Viewport::update() {
  const float x = objectToTrack->getX();
  const float y = objectToTrack->getY();
  viewX = (x + objWidth/2) - viewWidth/2;
  viewY = (y + objHeight/2) - viewHeight/2;
  if (viewX < 0) viewX = 0;
  if (viewY < 0) viewY = 0;
  
  if (viewX > (worldWidth - viewWidth)) {
    viewX = worldWidth-viewWidth;
  }
  if (viewY > (worldHeight - viewHeight)) {
    viewY = worldHeight-viewHeight;
  }
}
