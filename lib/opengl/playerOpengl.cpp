#include "math.h"
#include "opengl/gameOpengl.h"
#include "opengl/worldOpengl.h"
#include "opengl/playerOpengl.h"
#include "opengl/opengl.h"
#include <controls.h>

PlayerOpengl::PlayerOpengl(const char * _name, Controls *_controls, int skin, int id)
  :Player(_name, _controls, skin, id){
  flags=0;
  rotx=roty=rotz=0;
  keyPressed=0;
  accel=1;
  actionTime=0;
  rotateDirection = 0;
}


//Call propper function according to the key code given in parameter
bool PlayerOpengl::setPressedKey(int key, bool bKeyDown){
   if(playerState != PLAYER_ALIVE){
      keyPressed=0;
      return false;
   }

   if(controls->m_iType == CONTROLS_TYPE_KEYBOARD)
      return ((ControlsKeyboard*)controls)->handleInput(key, bKeyDown, &keyPressed);
   else
      return false;
}


void PlayerOpengl::processEvents(){

   /*if(keyPressed==0 
      || (keyPressed&KEY_LEFT && keyPressed&KEY_RIGHT)
      || (keyPressed&KEY_UP && keyPressed&KEY_DOWN))
      accel=1;*/

   int i=0;
   bool rotated = false;
   for(i=0;i<4;i++){
      if(keyPressed & (1<<i)){
         if((!rotated || rotateDirection!=i) && !((keyPressed != (1<<i)) && !canMove(i))){
            rotateDirection=i;
            rotated=true;
         }
      }
   }

   if(rotated)
      move(directions[rotateDirection][0],directions[rotateDirection][1]);

   if(directions[rotateDirection][2] != rotz)
      rotate(directions[rotateDirection][2]);

  if(keyPressed&KEY_PLANT)
    plantBomb();

}

void PlayerOpengl::move(float dx, float dy){
  float speed_ = speed;
  //float diff = fabs(getRotDif(directions[rotateDirection][2], rotz));
  //if(diff>5 && diff/200>1)
  //   speed/=diff/200;
  if(accel<5)accel+=world->timeDelay;
  /*if(diff>10)
     accel-=1*((GameOpengl*)game)->timeDelay;*/
  speed *= world->timeDelay*100*(4-4/accel);
  Player::move(dx, dy);
  if(directions[rotateDirection][2] != rotz)
  speed = speed_;
}

void PlayerOpengl:: rotate(int degree){
  int dif= getRotDif((int)rotz, degree);
  roty+=(dif<10 && dif>-10)?((roty<1 && roty>-1)?0:(roty>0)?-1:+1):(dif>0)?+1:-1;
  if(roty>30)roty=30;
  if(roty<-30)roty=-30;
  rotz+=-dif*world->timeDelay*4;
  if(rotz>360)rotz-=360;
  if(rotz<0)rotz+=360;
}

//Plant bomb
void PlayerOpengl::plantBomb(){
  if(world->worldData[x][y]->type==SPACE){
    delete world->worldData[x][y];
    world->worldData[x][y]=new BombOpengl(x,y, fire);
  }
}

void PlayerOpengl::Die(){
	actionTime=0;
	Player::Die();
}

int PlayerOpengl::getRotDif(int angle1, int angle2){
   angle1%=360;
   angle2%=360;
   int ret = angle1 - angle2;
   if(ret>180)ret=-(360-ret);
   if(ret<-180)ret=360+ret;
   return ret;
}
