#ifndef PARALLAX__H
#define PARALLAX__H

#include <vector>

#include "sprite.h"

using std::vector;

class Parallax {
   public:
      Parallax() : parallaxObjects() {};
      void addSprite(const string& s);
      void update(Uint32 ticks);
      void draw();
      
   private:
      vector<Sprite> parallaxObjects;
};
#endif
