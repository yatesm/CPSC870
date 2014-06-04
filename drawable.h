#ifndef DRAWABLE__H
#define DRAWABLE__H

#include <SDL/SDL.h>
#include <iostream>
#include "vector2d.h"

class Frame;

// Drawable is an Abstract Base Class (ABC) that
// specifies the methods that derived classes may
// and must have.
class Drawable {
public:
  Drawable(float x, float y, float xs, float ys) : coordinate(x, y), speed(xs, ys),
     initSpeed(xs, ys) { }
     
  Drawable(float x, float y, float xs, float ys, float ixs, float iys) : coordinate(x, y),
  	 speed(xs, ys), initSpeed(ixs, iys) {}

  Drawable(const Drawable& s) :
    coordinate(s.coordinate), speed(s.speed), initSpeed(s.initSpeed) { }
    
  Drawable(const Vector2D& coord, const Vector2D& speed) : coordinate(coord),
     speed(speed), initSpeed(speed) {}

  virtual ~Drawable() {}

  virtual void draw() const = 0;
  virtual void update(Uint32 ticks) = 0;
  virtual void setFrame(Frame * f) = 0;
  virtual void deleteFrame() = 0;

  float getX() const { return coordinate[0]; }
  float getY() const { return coordinate[1]; }
  void setX(float x) { coordinate[0] = x; }
  void setY(float y) { coordinate[1] = y; }
  
  void setXSpeed(float x) { speed[0] = x; }
  void setYSpeed(float y) { speed[1] = y; }
  float getXSpeed() const { return speed[0]; }
  float getYSpeed() const { return speed[1]; }
    
   void setXInitSpeed(float x) { initSpeed[0] = x; }
   void setYInitSpeed(float y) { initSpeed[1] = y; }
   float getXInitSpeed() const { return initSpeed[0]; }
   float getYInitSpeed() const { return initSpeed[1]; }
   
   void incrXSpeed(float x) { speed[0] += x;}
   void incrYSpeed(float y) { speed[1] += y;}
   
   Vector2D getCoordinate() const { return coordinate; }
   Vector2D getSpeed() const { return speed; }
   Vector2D getInitSpeed() const { return initSpeed; }
   
   void stop() { speed *= 0.0; }
   
   void setSpeed(Vector2D v) { speed = v;}
protected:
  Vector2D coordinate;
  Vector2D speed;
  Vector2D initSpeed;
};
#endif
