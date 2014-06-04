#ifndef SPRITE__H
#define SPRITE__H

#include "drawable.h"
#include "frame.h"
#include "factory.h"

class Sprite : public Drawable {
public:
  Sprite(float x, float y, float xs, float ys, Frame* f) : 
    Drawable(x, y, xs, ys), frame(f), isTracked(false), fleeStrategyCode(0) { }

  Sprite(float x, float y, float xs, float ys, float ixs, float iys, Frame* f) : 
    Drawable(x, y, xs, ys, ixs, iys), frame(f), isTracked(false), fleeStrategyCode(0) { }

  Sprite(float x, float y, float xs, float ys, float ixs, float iys, bool t, Frame* f) : 
    Drawable(x, y, xs, ys, ixs, iys), frame(f), isTracked(t), fleeStrategyCode(0) { }

  Sprite(const Sprite& s) :
    Drawable(s.getX(), s.getY(), s.getXSpeed(), s.getYSpeed()), 
             frame(s.frame), isTracked(s.isTracked), fleeStrategyCode(0) { }
             
   Sprite(const Vector2D coord, const Vector2D speed, Frame* f) :
      Drawable(coord, speed), frame(f), isTracked(false), fleeStrategyCode(0) {}
  // destructor doesn't delete anything because nothing was
  // created (new) in this class:
  virtual ~Sprite() {} 
  Frame *getFrame() { return frame; }
  const Frame *getFrame() const { return frame; }
  void  deleteFrame() { delete frame; }
  virtual void setFrame(Frame * f) { frame = f; }

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  Sprite& operator=(const Sprite&);

  virtual bool shooting() const { return false; }
  virtual void shoot() {}
  virtual void cullBullets() {}
  
  void stop() { setSpeed(Vector2D(0.0, 0.0)); }
  int getFleeStrategyCode() const { return fleeStrategyCode; }
  void setFleeStrategyCode(int s) { fleeStrategyCode = s; }

  void toggleTracked() { isTracked = !isTracked; }
  bool getTracked() { return isTracked; }
 
  virtual void save(std::fstream &out) const;
private:
  Frame * frame;
  bool isTracked;
  int fleeStrategyCode;
};
#endif
