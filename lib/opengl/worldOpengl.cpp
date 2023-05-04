#include "stdlib.h"
#include "opengl/worldOpengl.h"
#include "opengl/gameOpengl.h"
#include "opengl/opengl.h"
#include "support.h"
#include <unistd.h>

WorldOpengl::WorldOpengl(){
	World();
}

void WorldOpengl::loadWorld(const char* fileName){
   getCurTime(timeStart);
   lastTime = lastRedraw = timeStart;

   World::loadWorld(fileName);
   int x,y;
   for(x=0;x<worldWidth;x++)
      for(y=0;y<worldHeight;y++){
         worldData[x][y]->rotx=generateRandomFloat();
         worldData[x][y]->roty=generateRandomFloat();
         worldData[x][y]->rotz=generateRandomFloat();
      }
}

void WorldOpengl::ProcessEvents(){
   timeDelay=getTimeDiff(lastTime);

   if(timeDelay<10){
      usleep(10000-(int)(timeDelay*1000));
      timeDelay=getTimeDiff(lastTime);
   }
   getCurTime(lastTime);

   if(game)
      for(int x=0;x<((GameOpengl*)game)->playersCount;x++)
         ((PlayerOpengl*)game->players[x])->processEvents();
}

BombOpengl::BombOpengl(int x, int y, int fireLen):Bomb(x,y,fireLen){
  state=BOMB_PLANTED;
  roty = rotz = rotx = 0;
  getCurTime(actionTime);
  modifyTime(actionTime,2);
}
