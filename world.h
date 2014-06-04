#ifndef WORLD__H
#define WORLD__H
#include "frame.h"
#include "viewport.h"

class World {
public:
  World(Frame * const f) 
    : frame(f), worldX(0.0), worldY(0.0), view(Viewport::getInstance()) {}
    
  World(const World & w) : frame(w.frame), worldX(w.worldX), worldY(w.worldY), view(w.view) {}
  void update();
  void draw() const { frame->draw(static_cast<Sint16>(worldX), static_cast<Sint16>(worldY), 0, 0); }
  ~World() {}
  World& operator=(const World& w);

private:
  Frame * const frame;
  float worldX;
  float worldY;
  Viewport * const view;

};
#endif
