#ifndef __gameOpengl__
#define __gameOpengl__

#include "game.h"
#include "opengl/playerOpengl.h"
#include "support.h"

class GameOpengl : public Game {
  public:
    GameOpengl();
    virtual void AddPlayer(const char * name, Controls *controls, int skin);
    bool handleKey(unsigned char key);
    
};

extern GameOpengl * game;

#endif
