
#include "frame.h"

Frame::Frame( SDL_Surface* spr, SDL_Surface* scr,
    Uint16 sprite_width, Uint16 sprite_height,
    Sint16 src_x, Sint16 src_y)
  : sprite(spr), screen(scr),
    spriteWidth(sprite_width), spriteHeight(sprite_height),
    spriteSourceX(src_x), spriteSourceY(src_y) {
}

void Frame::draw(Sint16 x, Sint16 y) const {
  SDL_Rect src = { spriteSourceX, spriteSourceY, spriteWidth, spriteHeight };    
  SDL_Rect dest = {x, y, spriteWidth, spriteHeight };
  SDL_BlitSurface(sprite, &src, screen, &dest);
}

void Frame::draw(Sint16 sx, Sint16 sy, Sint16 dx, Sint16 dy) const {
  SDL_Rect src = { sx, sy, spriteWidth, spriteHeight };    
  SDL_Rect dest = {dx, dy, spriteWidth, spriteHeight };
  SDL_BlitSurface(sprite, &src, screen, &dest);
}
