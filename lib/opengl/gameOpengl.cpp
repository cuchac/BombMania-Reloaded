#include "gui/cegui.h"

#include "opengl/gameOpengl.h"
#include "support.h"
#include "opengl/draw.h"
#include "opengl/control.h"
#include "opengl/objects.h"

#include "stdio.h"
#include <unistd.h>


GameOpengl::GameOpengl():Game(){

}

//Handle player adding. This is because Im sclerotic and i would forgot to increment playerCount :))
void GameOpengl::AddPlayer(const char* name, Controls* controls, int skin){
  players[playersCount]=new PlayerOpengl(name,controls, skin, playersCount);
  players[playersCount]->placePlayer(-1,-1);
  playersCount++; 
}


bool GameOpengl::handleKey(unsigned char key){
   switch(key){
      case 27:
         if(!menu->isVisible(CEGui::wMainMenu))
            menu->showMenu(CEGui::wIngameMenu, true);
         return true;
   }
   return false;
}




