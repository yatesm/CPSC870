#ifndef FRAME__H
#define FRAME__H

#include <iostream>
#include <SDL/SDL.h>

#include "game.h"

class Frame {
public:
  // Must pass both width and height here because the sprite might
  // not consist of the whole surface, only part of the surface.
  Frame( SDL_Surface* spr, SDL_Surface* scr, Uint16 sprite_width, Uint16 sprite_height,
      Sint16 src_x, Sint16 src_y);
  Frame(const Frame *f) : sprite(f->sprite), screen(f->screen), spriteWidth(f->spriteWidth), spriteHeight(f->spriteHeight), spriteSourceX(f->spriteSourceX), spriteSourceY(f->spriteSourceY) {}
  void draw(Sint16 x, Sint16 y) const;
  void draw(Sint16 sx, Sint16 sy, Sint16 dx, Sint16 dy) const;
  Uint16 getWidth()  const { return spriteWidth; }
  Uint16 getHeight() const { return spriteHeight; }
  Sint16 getSourceX() const { return spriteSourceX; }
  Sint16 getSourceY() const { return spriteSourceY; }
  SDL_Surface * getSurface() const { return sprite; }
  SDL_Surface * getScreen() const { return screen; }

private:
  SDL_Surface * const sprite;
  SDL_Surface * const screen;
  const Uint16 spriteWidth;
  const Uint16 spriteHeight;
  const Sint16 spriteSourceX;
  const Sint16 spriteSourceY;
  Frame(const Frame&);
  Frame& operator=(const Frame&);
};

#endif
