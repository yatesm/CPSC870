#ifndef VIEWPORT__H
#define VIEWPORT__H
#include <SDL/SDL.h>

class Sprite;
class Viewport {
public:
  static Viewport* getInstance();
  void update();

  float getX() const { return viewX; }
  float getY() const { return viewY; }

  void setX(float x) { viewX = x; }
  void setY(float y) { viewY = y; }

  void setObjectToTrack(const Sprite *obj);

private:
  Viewport();
  static Viewport  *instance;
  float viewX;
  float viewY;
  Uint16 objWidth;
  Uint16 objHeight;  
  const Sprite *objectToTrack;  
  const int viewWidth;
  const int viewHeight;
  const int worldWidth;
  const int worldHeight;
  
  Viewport(const Viewport&);
  Viewport& operator=(const Viewport&);
};
#endif
