#ifndef ZOMBIE__H
#define ZOMBIE__H

#include "sprite.h"
#include "cmath"

class Zombie : public Sprite {
public:
  Zombie(float x, float y, float xs, float ys, Frame* f) : 
    Sprite(x, y, xs, ys, f) { }

  Zombie(float x, float y, float xs, float ys, float ixs, float iys, bool t, Frame* f) : 
    Sprite(x, y, xs, ys, ixs, iys, t, f) { }
             
   Zombie(const Vector2D coord, const Vector2D speed, Frame* f) :
      Sprite(coord, speed, f) {}
  // destructor doesn't delete anything because nothing was
  // created (new) in this class:
  virtual ~Zombie() {}
  
  virtual void draw() { Sprite::draw(); }
  virtual void update(Uint32 ticks) { Sprite::update(ticks); }
     
private:
  Zombie& operator=(const Zombie&);
};
#endif
