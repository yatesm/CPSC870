#include <vector>
#include <iostream>
#include <cmath>

#include "sprite.h"
#include "viewport.h"

void Sprite::save(std::fstream &out) const {
	out<<"<Sprite>"<<endl;
	out<<"<x>"<<getX()<<"</x>"<<endl;
	out<<"<y>"<<getY()<<"</y>"<<endl;
	out<<"<xSpeed>"<<getXSpeed()<<"</xSpeed>"<<endl;
	out<<"<ySpeed>"<<getYSpeed()<<"</ySpeed>"<<endl;		
	out<<"<xInitialSpeed>"<<getXInitSpeed()<<"</xInitialSpeed>"<<endl;
	out<<"<yInitialSpeed>"<<getYInitSpeed()<<"</yInitialSpeed>"<<endl;
	out<<"<frameString>"<< Factory::getInstance()->getFrameKey(frame) <<"</frameString>"<<endl;
	out<<"<isTracked>"<< isTracked <<"</isTracked>"<<endl;
	out<<"</Sprite>"<<endl;
}

void Sprite::draw() const { 
   Viewport *view(Viewport::getInstance());
   frame->draw(static_cast<Uint32>(coordinate[0] - view->getX()), 
                          static_cast<Uint32>(coordinate[1] - view->getY()));               
}

void Sprite::update(Uint32 ticks) { 
   float incr = speed[1] * static_cast<float>(ticks) * 0.001;
   coordinate[1] += incr;
   float height = static_cast<float>(frame->getHeight());
   if ( coordinate[1] < 0) {
       coordinate[1] = 1.0;
       speed[1] = fabs(speed[1]);
   }
   if ( coordinate[1] > Game::getInstance()->getWorldHeight()-height) {
      coordinate[1] = static_cast<float>(Game::getInstance()->getWorldHeight()-height);
      speed[1] = -fabs(speed[1]);
   }

   incr = speed[0] * static_cast<float>(ticks) * 0.001;
   coordinate[0] += incr;
   float width = static_cast<float>(frame->getWidth());
   if ( coordinate[0] < 0) {
      coordinate[0] = 1.0;
      speed[0] = fabs(speed[0]);
   }
   if ( coordinate[0] > Game::getInstance()->getWorldWidth()-width) {
      coordinate[0] = static_cast<float>(Game::getInstance()->getWorldWidth() - width);
      speed[0] = -fabs(speed[0]);
   }
}

Sprite& Sprite::operator=(const Sprite& s) {
	if(this != &s) {
		coordinate = s.coordinate;
		speed = s.speed;
		initSpeed = s.initSpeed;
		frame = s.frame;
	}
	return *this;
}
