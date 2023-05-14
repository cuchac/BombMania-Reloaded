#include "gui/cegui.h"

#include "opengl/opengl.h"
#include "opengl/control.h"
#include "opengl/gameOpengl.h"

int    xnew=0, xold=0, ynew=0, yold=0, znew=0, zold=0, stav=0;
int    x2=0, y2=0, z2=0;


void onMouse(int button, int state, int x, int y)
{
   if(CEGui::mouseButton(button, state, x, y))
      return;

   if (button==GLUT_LEFT_BUTTON) {
      if (state==GLUT_DOWN) {
         stav=1;
         x2=x;
         y2=y;
      }
      else {
         stav=0;
         xold=xnew;
         yold=ynew;
      }
   }
   if (button==GLUT_RIGHT_BUTTON) {
      if (state==GLUT_DOWN) {
         stav=2;
         z2=y;
      }
      else {
         stav=0;
         zold=znew;
      }
   }
}

void onMotion(int x, int y)
{
   CEGui::mouseMotion( x, y);

   if (stav==1) {
      xnew=xold+x-x2;
      ynew=yold+y-y2;
   }
   if (stav==2) {
      znew=zold+y-z2;
   }
}

void onSpecial(int key, int _x, int _y){
   
   if(game->handleKey(key))
      return;
   
   if(CEGui::keySpecial(key, _x, _y))
      return;
   
   if(game){
      key+=0xFF;
      for(int x=0;x<game->playersCount;x++)
         ((PlayerOpengl*)game->players[x])->setPressedKey(key, true);
   }
}

void onSpecialUp(int key, int _x, int _y){
   key+=0xFF;
   if(game)
      for(int x=0;x<game->playersCount;x++)		
         ((PlayerOpengl*)game->players[x])->setPressedKey(key, false);
}

void onKeyboard(unsigned char key, int x, int y)
{
   if(game->handleKey(key))
      return;
   
   if(CEGui::keyChar(key, x, y))
      return;
   
   if(game)
      for(int x=0;x<game->playersCount;x++)		
         ((PlayerOpengl*)game->players[x])->setPressedKey(key, true);
}

void onKeyboardUp(unsigned char key, int _x, int _y){
   /*if(CEGui::keyChar(key, x, y))
      return;*/
   if(game)
      for(int x=0;x<game->playersCount;x++)		
         ((PlayerOpengl*)game->players[x])->setPressedKey(key, false);
}

