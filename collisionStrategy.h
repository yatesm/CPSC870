#ifndef COLLISIONSTRATEGY__H
#define COLLISIONSTRATEGY__H
#include <cmath>
#include <vector>
#include "sprite.h"

using std::vector;

class Bullet;
class CollisionStrategy {
	public:
		virtual bool execute(const Sprite& s1, const Sprite& s2) const = 0;
		virtual bool execute(const Bullet& s1, const Sprite& s2) const = 0;
		virtual float distance(const Sprite& s1, const Sprite& s2) const;
		virtual ~CollisionStrategy() {}
};

class CircularCollisionStrategy : public CollisionStrategy {
	public:
		CircularCollisionStrategy() {}
		virtual bool execute(const Sprite& s1, const Sprite& s2) const;
		virtual bool execute(const Bullet& s1, const Sprite& s2) const;
		virtual float distance(const Sprite& s1, const Sprite& s2) const;
};

class RectangularCollisionStrategy : public CollisionStrategy {
	public:
		RectangularCollisionStrategy() {}
		virtual bool execute(const Sprite& s1, const Sprite& s2) const;
		virtual bool execute(const Bullet& s1, const Sprite& s2) const;		
		virtual float distance(const Sprite& s1, const Sprite& s2) const;
};

class CollisionSingleton {
	public:
		~CollisionSingleton();
		static CollisionSingleton* getInstance();
		const CollisionStrategy* operator[](const unsigned int i) const;
		CollisionStrategy* operator[](const unsigned int i);		
	private:
		vector<CollisionStrategy *> strategies;
		static CollisionSingleton *instance;
		CollisionSingleton();
		CollisionSingleton(const CollisionSingleton&);
		CollisionSingleton operator=(const CollisionSingleton&);
};

/* Not Yet Implemented */

/*class PerPixelCollisionStrategy : public CollisionStrategy {
public:
  PerPixelCollisionStrategy() {}
  virtual bool execute(const Sprite&, const Sprite&) const;
  virtual void draw() const;
};*/
#endif
