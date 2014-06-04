#include <iostream>

#include "sprite.h"	

class ExplodingSprite : public Sprite {
public:

  explicit ExplodingSprite(
    const Vector2D& pos, const Vector2D vel, Frame* fm) : Sprite(pos, vel, fm), 
    distance(0), maxDistance(Game::getInstance()->getWorldWidth()/2), 
    tooFar(false) { }
    
  ExplodingSprite(const Sprite& s)
    : Sprite(s), distance(0), maxDistance(Game::getInstance()->getWorldWidth()/10),
    	tooFar(false) {}
    	
  virtual void save(std::fstream& xmlfile) const;    	
  virtual void update(Uint32 ticks);
  virtual void cullBullets() {}
  virtual void shoot () {}
  bool goneTooFar() const { return tooFar; }
  void reset() {
    tooFar = false;
    distance = 0;
  }
private:
  float distance;
  float maxDistance;
  bool tooFar;
};
