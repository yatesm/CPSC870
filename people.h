#ifndef PEOPLE__H
#define PEOPLE__H

#include "sprite.h"
#include "bullet.h"

#include <cmath>
#include <vector>

using std::vector;

class People : public Sprite {
public:
  People(float x, float y, float xs, float ys, Frame* f) : 
    Sprite(x, y, xs, ys, f) { }
    
  People(float x, float y, float xs, float ys, float ixs, float iys, bool t, Frame* f) : 
    Sprite(x, y, xs, ys, ixs, iys, t, f) { }
             
   People(const Vector2D coord, const Vector2D speed, Frame* f) :
      Sprite(coord, speed, f) {}
  // destructor doesn't delete anything because nothing was
  // created (new) in this class:
  
  virtual void draw() const { Sprite::draw(); }
  virtual void update(Uint32 ticks) { Sprite::update(ticks); }
  virtual ~People() {} 
private:
  People& operator=(const People&);
};
#endif
