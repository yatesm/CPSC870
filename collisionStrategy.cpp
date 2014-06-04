#include "collisionStrategy.h"
#include "bullet.h"

CollisionSingleton* CollisionSingleton::getInstance() {
	if(!instance) instance = new CollisionSingleton();
	return instance;
}

const CollisionStrategy* CollisionSingleton::operator[](const unsigned int i) const {
	if(i < strategies.size())
		return strategies[i];
	return strategies[strategies.size() - 1];
}

CollisionStrategy* CollisionSingleton::operator[](const unsigned int i) {
	if(i < strategies.size())
		return strategies[i];
	return strategies[strategies.size() - 1];
}

CollisionSingleton::CollisionSingleton() : strategies() {
	strategies.push_back(new CircularCollisionStrategy);
	strategies.push_back(new RectangularCollisionStrategy);	
}

CollisionSingleton::~CollisionSingleton() {
   for(vector<CollisionStrategy *>::iterator it(strategies.begin()); it != strategies.end(); ++it)
	   delete (*it);   
	strategies.clear();   
}

bool CircularCollisionStrategy::execute(const Sprite& s1, const Sprite& s2) const {
	float distanceBetween = CollisionStrategy::distance(s1, s2);
	float s1Radius = ((s1.getFrame()->getWidth() / 2) + (s1.getFrame()->getHeight() / 2)) / 2;
	float s2Radius = ((s2.getFrame()->getWidth() / 2) + (s2.getFrame()->getHeight() / 2)) / 2;
	return(distanceBetween < (s1Radius + s2Radius));
}

bool CircularCollisionStrategy::execute(const Bullet& s1, const Sprite& s2) const {
	float distanceBetween = CollisionStrategy::distance(s1, s2);
	float s1Radius = ((s1.getFrame()->getWidth() / 2) + (s1.getFrame()->getHeight() / 2)) / 2;
	float s2Radius = ((s2.getFrame()->getWidth() / 2) + (s2.getFrame()->getHeight() / 2)) / 2;
	return(distanceBetween < (s1Radius + s2Radius));
}

float CircularCollisionStrategy::distance(const Sprite& s1, const Sprite& s2) const {	
	float dx, dy;
	dx = s1.getX() + (s1.getFrame()->getWidth() / 2) - 
				s2.getX() + (s2.getFrame()->getWidth() / 2);
				
	dy = s1.getY() + (s1.getFrame()->getHeight() / 2) -
			  s2.getY() + (s2.getFrame()->getHeight() / 2);
	return( sqrt( pow(dx, 2) + pow(dy, 2) ) );
}

bool RectangularCollisionStrategy::execute(const Sprite& s1, const Sprite& s2) const {
    float left1 = s1.getX();
    float left2 = s2.getX();
    float right1 = left1 + s1.getFrame()->getWidth();
    float right2 = left2 + s2.getFrame()->getWidth();
    float top1 = s1.getY();
    float top2 = s2.getY();
    float bottom1 = top1 + s1.getFrame()->getHeight();
    float bottom2 = top2 + s2.getFrame()->getHeight();
    if ( right1 < left2 ) return false;
    if ( left1 > right2 ) return false;
    if ( bottom1 < top2 ) return false;
    if ( bottom2 < top1 ) return false;
    return true;
}

bool RectangularCollisionStrategy::execute(const Bullet& s1, const Sprite& s2) const {
    float left1 = s1.getX();
    float left2 = s2.getX();
    float right1 = left1 + s1.getFrame()->getWidth();
    float right2 = left2 + s2.getFrame()->getWidth();
    float top1 = s1.getY();
    float top2 = s2.getY();
    float bottom1 = top1 + s1.getFrame()->getHeight();
    float bottom2 = top2 + s2.getFrame()->getHeight();
    if ( right1 < left2 ) return false;
    if ( left1 > right2 ) return false;
    if ( bottom1 < top2 ) return false;
    if ( bottom2 < top1 ) return false;
    return true;
}

float RectangularCollisionStrategy::distance(const Sprite& s1, const Sprite& s2) const {
	return(sqrt(pow(s1.getX() - s2.getX(), 2) + pow(s1.getY() - s2.getY(), 2)));
}

float CollisionStrategy::distance(const Sprite& s1, const Sprite& s2) const {
	return(sqrt(pow(s1.getX() - s2.getX(), 2) + pow(s1.getY() - s2.getY(), 2)));
}
