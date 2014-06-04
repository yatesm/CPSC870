#ifndef BULLET__H
#define BULLET__H
#include <cmath>
#include "sprite.h"

class Bullet : public Sprite 
{
   public:
      Bullet(float x, float y, float xs, float ys, Frame *f) :
         Sprite(x, y, xs, ys, f), distance(0) {}
      Bullet(Vector2D coordinate, Vector2D speed, Frame *f) :
         Sprite(coordinate, speed, f), distance(0) {}
      float getDistance() const { return distance; }
      void setDistance(float d) { distance = d; }
      void update(Uint32 ticks) 
      {
            float x = getX(), y = getY();
            float incr = speed[1] * static_cast<float>(ticks) * 0.001;
            coordinate[1] += incr;
            incr = speed[0] * static_cast<float>(ticks) * 0.001;
            coordinate[0] += incr;
            distance += fabs(x - getX()) + fabs(y - getY());
      }
      
       void shoot() {}
       bool shooting() const { return false; }

   private:
      Bullet();
      float distance;
};
#endif
