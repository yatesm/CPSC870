#include "fleeStrategy.h"

using std::vector;

FleeSingleton* FleeSingleton::getInstance() {
	if(!instance) instance = new FleeSingleton();
	return instance;
}

const FleeStrategy* FleeSingleton::operator[](const unsigned int i) const {
	if(i < strategies.size())
		return strategies[i];
	else
		return strategies[strategies.size() - 1];
}

FleeStrategy* FleeSingleton::operator[](const unsigned int i) {
	if(i < strategies.size())
		return strategies[i];
	else
		return strategies[strategies.size() - 1];
}


FleeSingleton::FleeSingleton() : strategies() {
   strategies.push_back(new AwayFleeStrategy);
   strategies.push_back(new PerpFleeStrategy);
   strategies.push_back(new PursueFleeStrategy);
}

FleeSingleton::~FleeSingleton() {
	for(vector<FleeStrategy *>::iterator it(strategies.begin()); it != strategies.end(); ++it)
	   delete (*it);   
	strategies.clear();
}

float FleeStrategy::distance(const Sprite& chaser, const Sprite& runner) const {
   return(sqrt(pow(chaser.getX() - runner.getX(), 2) + pow(chaser.getY() - runner.getY(), 2)));
}
   
Vector2D AwayFleeStrategy::flee(const Sprite& chaser, const Sprite& runner) const {
	Vector2D v(0.0, 0.0);
	v = Vector2D(chaser.getCoordinate() - runner.getCoordinate());
	v.normalize();
   v *= -1;
	return(v * runner.getInitSpeed());
}      

Vector2D PerpFleeStrategy::flee(const Sprite& chaser, const Sprite& runner) const {
   float holder;
	Vector2D v(0.0, 0.0);
	v = Vector2D(chaser.getCoordinate() - runner.getCoordinate());
	holder = v.getX();
	v.setX(v.getY() * -1);
	v.setY(holder);
	v.normalize();
	return(v * runner.getInitSpeed());
	
}   

Vector2D PursueFleeStrategy::flee(const Sprite& chaser, const Sprite& runner) const {
	float tempFloat;
	Vector2D v = Vector2D(runner.getCoordinate() - chaser.getCoordinate());
	tempFloat = sqrt(pow(chaser.getXSpeed(), 2) + pow(chaser.getYSpeed(), 2));
	v.normalize();
	v *= tempFloat;
	return(v);
}      

/*
Vector2D ComplexFleeStrategy::flee(const vector<Sprite *> chasers, const Sprite& runner) const {
   Vector2D v(0.0, 0.0);
   for(unsigned int i = 0; i < chasers.size(); ++i) {
      v += chasers[i]->getSpeed() * (distanceConstant / distance(*(chasers[i]), runner));
  }
  v.normalize();
  v *= runner.getInitSpeed();
  return(v);
} 

*/
