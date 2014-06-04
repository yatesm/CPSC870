#ifndef STATS__H
#define STATS__H

class Stats {
   public:
      Stats() : zombiesKilled(0), peopleShot(0), peopleEaten(0), timesDied(0), score(0) {}
     
      int getZombiesKilled() const { return zombiesKilled; }
      int getPeopleShot() const { return peopleShot; }
      int getPeopleEaten() const { return peopleEaten; }
      int getTimesDied() const { return timesDied; }
      
      void setZombiesKilled(int s) { zombiesKilled = s; }
      void setPeopleShot(int s) { peopleShot = s; }
      void setPeopleEaten(int s) { peopleEaten = s;}
      void setTimesDied(int s) { timesDied = s; }
      
      int getScore() const { return score; }
      void setScore(int s) { score = s; }
      virtual void calculateScore() {};
      virtual ~Stats() {}
   private:
      int zombiesKilled;
      int peopleShot;
      int peopleEaten;
      int timesDied;
      int score;
};

class PlayerStats : public Stats {
   public:
      PlayerStats() : Stats() {}
      virtual void calculateScore() { setScore((50 * getZombiesKilled()) - 
                                             (10 * getPeopleEaten()) - (25 * getPeopleShot()) - 
                                             (50 * getTimesDied())); }
};

class ZombieStats : public Stats {
   public:
      ZombieStats() : Stats() {}
      virtual void calculateScore() { setScore((0 * getZombiesKilled()) + 
                                          (50 * getPeopleEaten()) + (25 * getPeopleShot()) - 
                                             (50 * getTimesDied())); }      
};
#endif
