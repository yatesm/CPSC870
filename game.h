#ifndef GAME__H
#define GAME__H
#include <iostream>
#include <map>
#include <string>

#include "parseXML.h"
//#include "factory.h"

using std::string;

class SpriteData {
public:
  friend class Game;
  SpriteData() : fname(NULL), width(0), height(0), srcx(0), srcy(0), colorkey(false) {}
  SpriteData(string s, unsigned w, unsigned h, unsigned sx, unsigned sy, bool ckey)
    : fname(s), width(w), height(h), srcx(sx), srcy(sy), colorkey(ckey) { cout<<"constructing "<<fname<<endl;}
  unsigned getWidth() const { return width; }
  unsigned getHeight() const { return height; }
  unsigned getSpriteSrcX() const { return srcx; }
  unsigned getSpriteSrcY() const { return srcy; }
  string getFname() const { return fname; }
  bool getColorKey() const { return colorkey; }
private:
  string fname;
  unsigned width;
  unsigned height;
  unsigned srcx;
  unsigned srcy;
  bool colorkey;
};

class Game {
public:
  static Game* getInstance();
  void print() const;
  const SpriteData getData(const string& s) const;
  void addData(const char * fileName, unsigned w, unsigned h, unsigned sx, unsigned sy, bool ckey);
  unsigned getWorldWidth() const { return worldWidth; }
  unsigned getWorldHeight() const { return worldHeight; }
  unsigned getViewWidth() const { return viewWidth; }
  unsigned getViewHeight() const { return viewHeight; }  
  unsigned getChunkSize() const { return chunkSize; }
  unsigned getMaxDistance() const { return maxDistance; }
  unsigned getExplosionSpeed() const { return explosionSpeed; }
  unsigned getZombieCount() const { return zombieCount; }
  unsigned getPeopleCount() const { return peopleCount; }
  unsigned getFontSize() const { return fontSize; }
  unsigned getMaxString() const { return maxString; }
  unsigned getBulletSpeed() const { return bulletSpeed; }
  unsigned getMaxBulletDistance() const { return maxBulletDistance; }
  unsigned getInitialHumans() const { return initialHumans; }
  unsigned getInitialZombies() const { return initialZombies; }
  void makeSpriteData();
  void debug(const std::multimap<string, string>& xmlData);
  void handleGameData();
  
//  const std::multimap<string, string>& getMusicData() const { return musicData; }
//  const std::multimap<string, string>& getSoundData() const { return soundData; }    
  ~Game();
private:
  ParseXML *parser;
//  Factory *fact;
  HandleChars * gameDataHandle;
  HandleChars * imageDataHandle;
//  HandleChars * soundDataHandle;
//  HandleChars * musicDataHandle;
  std::multimap<string, string> gameData;  
  std::multimap<string, string> imageData;
//  std::multimap<string, string> soundData;
//  std::multimap<string, string> musicData;
  
  unsigned worldWidth; //World Constants
  unsigned worldHeight;
  unsigned viewWidth;  //Viewport Constants
  unsigned viewHeight;  
  
  unsigned chunkSize; // For generating explosions
  unsigned maxDistance;  //Also for explosions
  unsigned explosionSpeed;  //Also for explosions
  
  unsigned zombieCount;  //Sprite Initialization Constant
  unsigned peopleCount;  //Sprite Initialization Constant
  
  unsigned fontSize;  //ioManager constants
  unsigned maxString;  //ioManager constants

  unsigned bulletSpeed;
  unsigned maxBulletDistance;
  
  unsigned initialHumans;
  unsigned initialZombies;  
  std::map<string, SpriteData> spriteMap;
  static Game* instance;
  Game();
  Game(const Game&);
  Game& operator=(const Game&);
};
#endif
