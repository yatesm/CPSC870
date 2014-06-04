#include <iostream>
#include <cmath>

#include "explodingSprite.h"

void ExplodingSprite::update(Uint32 ticks) { 
  float yincr = speed[1] * static_cast<float>(ticks) * 0.001;
  coordinate[1] = coordinate[1] - yincr ;
  float xincr = speed[0] * static_cast<float>(ticks) * 0.001;
  coordinate[0] = coordinate[0] - xincr ;
  distance += ( hypot(xincr, yincr) );
  if (distance > Game::getInstance()->getMaxDistance()) tooFar = true;
}


void ExplodingSprite::save(std::fstream& xmlfile) const {
  xmlfile << "<ExplodingSprite>" << endl;

  xmlfile << "<distance>" << distance << "</distance>" << endl;
  xmlfile << "<maxDistance>" << maxDistance << "</maxDistance>" << endl;
  xmlfile << "<tooFar>" << tooFar << "</tooFar>" << endl;
  
  Sprite::save(xmlfile);
  xmlfile << "</ExplodingSprite>" << endl;
}
