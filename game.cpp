#include <fstream>
#include <map>
#include <cstdlib>
#include "game.h"
#include "handleChars.h"

using std::cout; using std::endl;
using std::map;
Game* Game::getInstance() {
  if ( !instance ) instance = new Game;
  return instance;
}

// std::ws -- Extracts as many whitespace characters as possible 
// from the current position in the input sequence. The extraction 
// stops as soon as a non-whitespace character is found.
Game::Game() : parser(ParseXML::getInstance()), //fact(Factory::getInstance()),
                           gameDataHandle(new HandleChars), 
                            imageDataHandle(new HandleChars), 
                            //soundDataHandle(new HandleChars),
                            //musicDataHandle(new HandleChars),
                            gameData(), imageData(), /* soundData(), musicData(),*/
                            worldWidth(0), worldHeight(0), viewWidth(0), viewHeight(0),
									 chunkSize(0), maxDistance(0), explosionSpeed(0), zombieCount(0),
									 peopleCount(0), fontSize(0), maxString(0), bulletSpeed(0),
									 maxBulletDistance(0), initialHumans(0), initialZombies(0), spriteMap() {
  parser->parseXML("data/imageData.xml", imageDataHandle);
  imageData = imageDataHandle->getData();
  makeSpriteData();
  std::multimap<string, string>::iterator it =  imageData.begin();
  parser->parseXML("data/gameData.xml", gameDataHandle);
  gameData = gameDataHandle->getData();
  handleGameData();
/*  parser->parseXML("data/soundData.xml", soundDataHandle);  
  soundData = soundDataHandle->getData();
  parser->parseXML("data/musicData.xml", musicDataHandle);
  */
}

void Game::debug(const multimap<string, string>& xmlData) {
  multimap<string, string>::const_iterator ptr = xmlData.begin();
  cout << "XML Data:" << endl;
  while ( ptr != xmlData.end() ) {
    cout << "(" << ptr->first << ", " << ptr->second << ")" << endl;
    ++ptr;
  }
}

void Game::handleGameData() {
   std::multimap<string, string>::iterator it = gameData.begin();
   for( ; it != gameData.end(); ++it)
		cout<<"("<<it->first<<", "<<it->second<<")"<<endl;
	it = gameData.begin();
   bulletSpeed = atoi(it->second.c_str());
   ++it;
   chunkSize = atoi(it->second.c_str());
   ++it;
   maxDistance = atoi(it->second.c_str());
   ++it;
   explosionSpeed = atoi(it->second.c_str());
   ++it;
   initialHumans = atoi(it->second.c_str());
   ++it;
	initialZombies = atoi(it->second.c_str());
	++it;
   fontSize = atoi(it->second.c_str());
   ++it;
   maxString = atoi(it->second.c_str());
   ++it;
   maxBulletDistance = atoi(it->second.c_str());
   ++it;
   peopleCount = atoi(it->second.c_str());
   ++it;
   viewHeight = atoi(it->second.c_str());
   ++it;
   viewWidth = atoi(it->second.c_str());
   ++it;
   worldHeight = atoi(it->second.c_str());
   ++it;
   worldWidth = atoi(it->second.c_str());
   ++it;
   zombieCount = atoi(it->second.c_str());
}
  

void Game::makeSpriteData() {
   int w, h, sx, sy;
   bool ckey;
   string fname;
   std::multimap<string, string>::iterator it =  imageData.begin();
   while(it != imageData.end()) {
      if(it->second == "false")
         ckey = false;
      else if(it->second == "true")
         ckey = true;
      it++;      
      fname = it->second;
      ++it;
      h = atoi(it->second.c_str());
      ++it;
      sx = atoi(it->second.c_str());
      ++it;      
      sy = atoi(it->second.c_str()); 
      ++it;      
      w = atoi(it->second.c_str());
		spriteMap.insert(std::map<string, SpriteData>::value_type(fname, SpriteData(fname, w, h, sx, sy, ckey)));
      ++it;
   }
}

/*void Game::loadFactory() {
   map<string, SpriteData>::iterator it = spriteMap.begin();
   while(it != spriteMap.end())
      fact->makeStuff(it->first, it->second);
}*/

const SpriteData Game::getData(const string& s) const {
  std::map<string, SpriteData>::const_iterator pos = spriteMap.begin(); 
  if(pos != spriteMap.end())
  while ( pos != spriteMap.end() ) {
    if (s == pos->first) return pos->second;
    else 
    {
    ++pos;
    }
  }
  if ( pos == spriteMap.end() ) {
    throw std::string("Couldn't find SpriteData");
  }
  return SpriteData();
}

void Game::print() const {
  std::map<string, SpriteData>::const_iterator pos = spriteMap.begin(); 
  while ( pos != spriteMap.end() ) {
    cout << pos->first << " ," 
         << pos->second.width << ", "
         << pos->second.height << ", "
         << pos->second.srcx << ", "
         << pos->second.srcy << ", "
         << pos->second.colorkey << ", "
         << endl;
    ++pos;
  }
}

Game::~Game() {
	delete gameDataHandle;
	delete imageDataHandle;
   spriteMap.clear();
}
