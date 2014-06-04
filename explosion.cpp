#include <iostream>
#include <cmath>
#include <vector>
using std::vector;

#include "explosion.h"
#include "ioManager.h"

Explosion::Explosion(const Sprite& s, const string& st) : Sprite(s), 
	screen(s.getFrame()->getScreen()),   frame(s.getFrame()),
	surface(frame->getSurface()), chunks(), fileName(st) {
		makeChunks(Game::getInstance()->getChunkSize());
}

Explosion::Explosion(string st, float x, float y, float xs, float ys, Frame* f) :
	Sprite(x, y, xs, ys, f), screen(f->getScreen()), frame(f), surface(f->getSurface()), chunks(), fileName(st) {
		makeChunks(Game::getInstance()->getChunkSize());
}

Explosion::~Explosion() { 
  for(unsigned int i = 0; i < chunks.size(); ++i)
   delete(chunks[i].getFrame());
  chunks.clear();
}

void Explosion::draw() const { 
  for (unsigned int i = 0; i < chunks.size(); ++i) {
    chunks[i].draw();
  }
}

void Explosion::update(Uint32 ticks) { 
  vector<ExplodingSprite>::iterator ptr = chunks.begin();
  while (ptr != chunks.end()) {
    ptr->update(ticks);
    if (ptr->goneTooFar()) {
    		ptr->setSpeed(ptr->getSpeed() * 0.0);
    }   
    ++ptr;
  }
}

void Explosion::save(std::fstream& xmlfile) const { 
	Sprite::save(xmlfile);
}

void Explosion::makeChunks(unsigned int n) { 
  unsigned int chunk_width = frame->getWidth()/n;
  unsigned int chunk_height = frame->getHeight()/n;
  Sint16 source_x = frame->getSourceX();
  Sint16 source_y = frame->getSourceY();
  float explosionSpeed = Game::getInstance()->getExplosionSpeed();
  for (unsigned int i = 0; i < n; ++i) {
    for (unsigned int j = 0; j < n; ++j) {
      float speed_x = (rand() % 10) * (rand()%2?-1:1); 
      float speed_y = (rand() % 10) * (rand()%2?-1:1); 
      Vector2D speeds(speed_x, speed_y);
      speeds.normalize();
      speeds *= explosionSpeed;
      Sprite sprite(
                Vector2D( getX() +i*chunk_width,  // x coord of destination 
                getY()+j*chunk_height), // y coord of destination
                speeds,
                new Frame(surface, screen, chunk_width, chunk_height,
                source_x+i*chunk_width,  // x coord of surface
                source_y+j*chunk_height) // y coord of surface
                );
      chunks.push_back(sprite);
    }
  }
}

