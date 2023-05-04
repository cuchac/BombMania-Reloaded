#include "gui/cegui.h"

#include "opengl/opengl.h"
#include "opengl/gameOpengl.h"
#include "opengl/worldOpengl.h"
#include "stdio.h"


int windowWidth=WINDOW_WIDTH, windowHeight=WINDOW_HEIGHT;


void onResize (int width, int height)
{
   CEGui::reshape(width, height);
   
  windowWidth=width;
  windowHeight=height;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, windowWidth, windowHeight);
  setCamera();
  glutPostRedisplay();
}

void onIddle(){
  glutPostRedisplay();
}

void onDisplay(void)
{
   if(game){
      world->redrawDelay=getTimeDiff(world->lastRedraw);

      if(world->redrawDelay<20){
         usleep(20000-(int)(world->redrawDelay*1000));
         world->redrawDelay=getTimeDiff(world->lastRedraw);
      }
      getCurTime(world->lastRedraw);
   }

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   setCamera();

   //drawEnv();
   
   int x;
   if(game){
      for(x=0;x<world->worldWidth;x++)
         for(int y=0;y<world->worldHeight;y++)
            world->worldData[x][y]->Draw();

      for(x=0;x<((GameOpengl*)game)->playersCount;x++)		
         ((GameOpengl*)game)->players[x]->Draw();
   }
   
   menu->drawFrame();
   
   glFlush();
   glutSwapBuffers();
   glutPostRedisplay();
}



void setCamera(){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(FOVY, (GLfloat)windowWidth/(GLfloat)windowHeight, MIN_DIST, MAX_DIST);
  
  glTranslatef(0,0, -850);
  glTranslatef(0.0f, 0.0f, -znew);
  glRotatef(-39, 1.0f, 0.0f, 0.0f);
  glRotatef(ynew, 1.0f, 0.0f, 0.0f);
  glRotatef(xnew, 0.0f, 0.0f, 1.0f);
  glTranslatef(-800/2+140, -800/2+130, 0);
  //glRotatef(roty, 0.0f, 1.0f, 0.0f);
}


void Space::Draw(){
  //drawObject(&asteroid01, x*WORLD_SCALE, y*WORLD_SCALE, 0, ynew, 0, xnew,0.4);
}

void WallBrk::Draw(){
  switch(state){
    case STATE_INITIALIZED:
      drawObject(asteroid03, x*WORLD_SCALE, y*WORLD_SCALE, 0, rotx, roty, rotz,0.4);
      break;
    case STATE_DESTROYED:
      
      actionTime += world->redrawDelay;
      glDisable(GL_LIGHTING);
      glDisable(GL_DEPTH_TEST);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA,GL_ONE);
      glColor4f(1.0, 1.0, 1.0, (float)((50-(float)actionTime*50)/50));
      drawObject(explosionRed,  x*WORLD_SCALE, y*WORLD_SCALE, 0, rotx, roty, rotz,actionTime*20+20);
      drawObject(asteroid03,  x*WORLD_SCALE, y*WORLD_SCALE, 0, rotx, roty, rotz,0.4);
      glDisable(GL_BLEND);
      glEnable(GL_DEPTH_TEST);
      glEnable(GL_LIGHTING);
      break;
  }
  if(actionTime>1)WorldPiece::Destroy();
}

void WallUnBrk::Draw(){
  drawObject(asteroid02,  x*WORLD_SCALE, y*WORLD_SCALE, 0, rotx, roty, rotz,0.4);	
}

void Bomb::Draw(){
	float test;
  switch(((BombOpengl*)this)->state){
    case BOMB_PLANTED:
      rotz+=world->redrawDelay*100;
      if(!boomed)drawObject(mine,  x*WORLD_SCALE, y*WORLD_SCALE, 0, rotx, roty, rotz, 1.2);

	  test = getTimeDiff(((BombOpengl*)this)->actionTime);
      if(test>0){
        Boom();
        modifyTime(((BombOpengl*)this)->actionTime,1);
        ((BombOpengl*)this)->state = BOMB_BOOMED;
      }
      break;
    case BOMB_BOOMED:
      int phase=200+getTimeDiff(((BombOpengl*)this)->actionTime)*200;
      glDisable(GL_LIGHTING);
      glDisable(GL_DEPTH_TEST);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA,GL_ONE);
      glColor4f(1.0, 1.0, 1.0, (float)((200-(float)phase)/200));
      drawObject(explosion,  x*WORLD_SCALE, y*WORLD_SCALE, 0, rotx, roty, rotz,phase);
      glDisable(GL_BLEND);
      glEnable(GL_DEPTH_TEST);
      glEnable(GL_LIGHTING);

      if(getTimeDiff(((BombOpengl*)this)->actionTime)>0){
        Clean();
        ((BombOpengl*)this)->state = BOMB_CLEANED;
        world->worldData[x][y]=new Space(x,y);
        delete this;
      }
      break;
  }
 }

void Player::Draw(){
  float time=0;
  int x;
  switch(playerState){
    case PLAYER_OUT:
      time = ((PlayerOpengl*)this)->actionTime += world->redrawDelay;
      char message[100];
      char * name;
      name = 0;
      for(x=0;x<game->playersCount;x++)
        if(game->players[x]->playerState==PLAYER_ALIVE)name=game->players[x]->name;
       if(!name)
         sprintf(message,"Round over! Draw!");
       else
         sprintf(message,"Round over! Winner is: %s", name);
       /*glColor3f(1,1,0);
       drawString(100, 300, -10, message );*/
       menu->messageBox(message);
      if(time>3){
         menu->showMenu(CEGui::wMessageBox, false);
         playerState=GAME_OVER;
      }
      break;
    case GAME_OVER:
      for(x=0;x<game->playersCount;x++){
         game->players[x]->placePlayer(-1,-1);
         game->players[x]->playerState=PLAYER_ALIVE;
      }
      world->reload();
      
      break;
    case PLAYER_ALIVE:
      switch(skin){
        case 0:
          drawObject(ship01,  _x*WORLD_SCALE, _y*WORLD_SCALE, 0, rotx, roty, rotz);
          break;
        case 1:
          drawObject(ship02,  _x*WORLD_SCALE, _y*WORLD_SCALE, 0, rotx, roty, rotz,0.8);
          break;
        default:
          drawObject(ship01,  _x*WORLD_SCALE, _y*WORLD_SCALE, 0, rotx, roty, rotz);
      }
      break;
    case PLAYER_DEATH:
      printf("%e,   %e,      %e\n",time, ((PlayerOpengl*)this)->actionTime, world->redrawDelay);
      ((PlayerOpengl*)this)->actionTime += world->redrawDelay;
      time = ((PlayerOpengl*)this)->actionTime;
      glDisable(GL_LIGHTING);
      glDisable(GL_DEPTH_TEST);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA,GL_ONE);
      glColor4f(1.0, 1.0, 1.0, ((50-time*40)/50));
      switch(skin){
        case 0:
          drawObject(ship01,  _x*WORLD_SCALE, _y*WORLD_SCALE, 0, rotx, roty, rotz);
          break;
        case 1:
          drawObject(ship02,  _x*WORLD_SCALE, _y*WORLD_SCALE, 0, rotx, roty, rotz,0.8);
          break;
        default:
          drawObject(ship01,  _x*WORLD_SCALE, _y*WORLD_SCALE, 0, rotx, roty, rotz);
      }
      drawObject(explosionSun,  _x*WORLD_SCALE, _y*WORLD_SCALE, 0, rotx, roty, rotz,time*70+20);
      glDisable(GL_BLEND);
      glEnable(GL_DEPTH_TEST);
      glEnable(GL_LIGHTING);
      if(time>2){
        playerState=PLAYER_OUT;
        ((PlayerOpengl*)this)->actionTime=0;
      }
      break;
  }
 
}

void Fire::Draw(){
  //drawObject(asteroid01, x*WORLD_SCALE, y*WORLD_SCALE, 0, 0, 0, xnew,0.2);	
};

float fps;

void showFps(){
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glRasterPos3f(0, 0 , 0);
    char string[20], *pos;
    glColor3f(1, 1, 0);
    float delay = world->redrawDelay;
    //if(delay>0.001)
      fps = fps*(9.0f/10.0f)+(1.0f/10.0f)*(1.0f/delay);
    //fps = 1/((GameOpengl*)game)->timeDelay;
    sprintf(string,"%.d",(int)fps);
    pos = string;
    while(*pos){
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *pos);
      pos++;
    }
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
}

void drawEnv(){
  float rotate = getTimeDiff(world->timeStart);
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE);
  glColor4f(1.0, 1.0, 1.0, 1);
  drawObject(background,  0, 0, 0, 0, 0, 0, 5000);
  
  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  
  drawObject(jupiter,  300, 300, -4000, -30, rotate/2, 0, 300);

}

void drawString(int x, int y, int z, char * string, void * font)
{
  char * pos;
  
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_DEPTH_TEST);
  glRasterPos3f(x, y , z);
  
  pos = string;
  while(*pos){
    glutBitmapCharacter(font, *pos);
    pos++;
  }
  
  glEnable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
}

void * drawThreadProc(void * parms){
  while(1==1){
    world->ProcessEvents();
  }
  return 0;
}

void drawObject(int object, float x, float y, float z, float rotx, float roty, float rotz, float scale)
{

   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   glTranslatef(x, y, z);

   glRotatef(rotz, 0.0f, 0.0f, 1.0f);
   glRotatef(rotx, 1.0f, 0.0f, 0.0f);
   glRotatef(roty, 0.0f, 1.0f, 0.0f);
    

   glScalef(scale,scale,scale);

   glCallList(object);
    
   glPopMatrix();
 
}


