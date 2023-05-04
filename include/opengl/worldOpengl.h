#ifndef __worldOpengl__
#define __worldOpengl__

#include "world.h"
#include "support.h"
//Class representing the level=world. Keeps the data
class WorldOpengl : public World{
   public:
      timespec timeStart, lastTime, lastRedraw;
      float timeDelay, redrawDelay;
      void loadWorld(const char * fileName);
      WorldOpengl();
      virtual void ProcessEvents();
};

extern WorldOpengl * world;

#define BOMB_PLANTED  1
#define BOMB_BOOMED   2
#define BOMB_CLEANED  3

class BombOpengl:public Bomb{
  public:
    timespec actionTime;
    int state;
    BombOpengl(int x, int y, int fireLen);
};
#endif
