#ifndef FLEESTRATEGY__H
#define FLEESTRATEGY__H
#include <cmath>
#include <vector>
#include "sprite.h"
#include "vector2d.h"

using std::vector;

class FleeStrategy {
   public:
      virtual Vector2D flee(const Sprite& chaser, const Sprite& runner) const = 0;
      float distance(const Sprite& chaser, const Sprite& runner) const;
      virtual ~FleeStrategy() {}
};

class AwayFleeStrategy : public FleeStrategy {
   public:
      AwayFleeStrategy() {}
      virtual Vector2D flee(const Sprite& chaser, const Sprite& runner) const;
};

class PerpFleeStrategy : public FleeStrategy {
   public:
      PerpFleeStrategy() {}
      virtual Vector2D flee(const Sprite& chaser, const Sprite& runner) const;
};

class PursueFleeStrategy : public FleeStrategy {
   public:
      PursueFleeStrategy() {}
      virtual Vector2D flee(const Sprite& chaser, const Sprite& runner) const;
};

class ComplexFleeStrategy : public FleeStrategy {
   public:
      ComplexFleeStrategy() : distanceConstant(0.01) {}
      virtual Vector2D flee(const vector<Sprite *> chasers, const Sprite& runner) const;
   private:
      const float distanceConstant;
};

class FleeSingleton {
	public:
		~FleeSingleton();
		static FleeSingleton* getInstance();
		const FleeStrategy* operator[](const unsigned int i) const;
		FleeStrategy* operator[](const unsigned int i);		
	private:
		vector<FleeStrategy *> strategies;
		static FleeSingleton *instance;
		FleeSingleton();
		FleeSingleton(const FleeSingleton&);
		FleeSingleton operator=(const FleeSingleton&);
};
#endif
