#ifndef EXPLOSION__H
#define EXPLOSION__H
#include <vector>
#include <iostream>
using std::vector;

#include "explodingSprite.h"

const int CHUNKS = 15;

class Explosion : public Sprite {
public:
  Explosion(const Sprite& s, const string& st);
  Explosion(string, float, float, float, float, Frame *);
  ~Explosion();
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  void makeChunks(unsigned int);
  void makePerfectChunks(unsigned int);
  unsigned int chunkCount() const { return chunks.size(); }
  virtual void save(std::fstream& xmlfile) const;
private:
  SDL_Surface *screen;
  const Frame * const frame;
  SDL_Surface *surface;
  std::vector<ExplodingSprite> chunks;
  Explosion(const Explosion&);
  Explosion& operator=(const Explosion&);
  string fileName;
};
#endif
