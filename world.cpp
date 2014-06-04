#include <iostream>
#include "world.h"

void World::update() {
  worldX = view->getX();
  worldY = view->getY();
}
