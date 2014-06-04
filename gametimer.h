#ifndef GAMETIMER__H
#define GAMETIMER__H
#include <SDL/SDL.h>

class GameTimer 
{
   public:
      GameTimer() : curTicks(0), prevTicks(0), ticks(0), saveTicks(0), frames(0), 
      totalTicks(0), shootIntervalTicks(0), trackIntervalTicks(0), initialTime(0), loadedTime(0) {}
  
      Uint32 getTicks() 
      {
         prevTicks = curTicks;
         curTicks = SDL_GetTicks();
         ticks = curTicks-prevTicks;
         totalTicks += ticks;
         shootIntervalTicks += ticks;
         trackIntervalTicks += ticks;
         ++frames;
         return ticks;
      }
      float fps() const { return frames/(0.001*totalTicks); }
      Uint32 getSavedTicks() const { return saveTicks; }
      Uint32 getTotalTicks() const { return totalTicks; }
      Uint32 getShootIntervalTicks() const { return shootIntervalTicks; }
      Uint32 getTrackIntervalTicks() const { return trackIntervalTicks; }
      Uint32 getCurTicks() const { return curTicks; }
      Uint32 getPrevTicks() const { return prevTicks; }
      
      void setCurTicks(Uint32 t) { curTicks = t; }
      void setPrevTicks(Uint32 t) { prevTicks = t; }
      void setTicks(Uint32 t) { ticks = t; }
      void setTotalTicks(Uint32 t) { totalTicks = t; }
      void setSavedTicks(Uint32 t) { saveTicks = t; }
      void setShootIntervalTicks(Uint32 t) { shootIntervalTicks = t; }
      void setTrackIntervalTicks(Uint32 t) { trackIntervalTicks = t; }
      void pause() { saveTicks = ticks; }
      void unpause() { curTicks = SDL_GetTicks(); }
      
   private:
      Uint32 curTicks;
      Uint32 prevTicks;
      Uint32 ticks;
      Uint32 saveTicks;
      int frames;
      Uint32 totalTicks;
      Uint32 shootIntervalTicks;
      Uint32 trackIntervalTicks;
      Uint32 initialTime;
      Uint32 loadedTime;
};
#endif
