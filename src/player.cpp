#include <stdlib.h>
//#include <time.h>
#include <math.h>

#ifndef _WIN32
#include <unistd.h>
#endif

#include <opengl/worldOpengl.h>
#include <opengl/gameOpengl.h>
#include "player.h"
#include "bombmania.h"
#include "controls.h"
#include <string.h>

int directions[4][3]={
   {0,-1,180},
   {1,0,270},
   {0,1,0},
   {-1,0,90}
};

//Call propper function according to the key code given in parameter
bool Player::handleKey(int key){
	if(playerState != PLAYER_ALIVE)return false;

   int keyPressed = 0;
   if(controls->m_iType == CONTROLS_TYPE_KEYBOARD)
      return ((ControlsKeyboard*)controls)->handleInput(key, true, &keyPressed);
   else
      return false;
	
   if(keyPressed==KEY_LEFT)
			move(directions[LEFT][0],directions[LEFT][1]); 
   else if(keyPressed==KEY_RIGHT)
			move(directions[RIGHT][0],directions[RIGHT][1]);
   else if(keyPressed==KEY_UP)
			move(directions[UP][0],directions[UP][1]);
   else if(keyPressed==KEY_DOWN)
			move(directions[DOWN][0],directions[DOWN][1]);
   else if(keyPressed==KEY_PLANT)
			plantBomb();
	else return false;
	return true;
}

//Plant bomb
void Player::plantBomb(){
	if(world->worldData[x][y]->type==SPACE){
		delete world->worldData[x][y];
		world->worldData[x][y]=new Bomb(x,y, fire);
	}
}

//Destroy player -> count-
void Player::Destroy(){
	game->playersCount--;
	delete this;
}

//Move player given direction
void Player::move(float dx, float dy)
{

   //Get the direction "vector"
   float dirx = (dx==0)?0:(dx>0)?1:-1;
   float diry = (dy==0)?0:(dy>0)?1:-1;

	//Signalize the small BombHack
	bool hacked=false;

	//Handle situation when standing on the bomb -> really stupid idea to be still there :)))
	if(world->worldData[x][y]->type==BOMB){
		world->worldData[x][y]->type=SPACE;
		hacked=true;
	}

   int newx = roundMin(_x+dirx/2);
   int newy = roundMin(_y+diry/2);

   if(newx>=0 && newy>=0 && newx<world->worldWidth && newy<world->worldHeight)
      if((dx*speed < 1) && (dy*speed<1))

         //Basic movement restriction -> Dont walk through the walls :))
         if( (world->worldData[newx][newy]->type<=FIRE) &&
            (world->worldData[newx][newy]->type<=FIRE))
         {
            _x+=dx*speed;
            _y+=dy*speed;

            //Advanced centering when moving -> Run, run, round the corner :)
            if(dx!=0 && (fabs(_y - round(_y)))>THREASHOLD)
               _y+=(((_y - round(_y))<0)?speed/2:-speed/2);
            
            if(dy!=0 && (fabs(_x - round(_x)))>THREASHOLD)
               _x+=(((_x - round(_x))<0)?speed/2:-speed/2);	
	}

	if(hacked)
		world->worldData[x][y]->type=BOMB;


	//Keep inherited x,y variables updated
	x=round(_x);
	y=round(_y);

	game->CheckAlive();

}

//Constructor of Player. It is necesary to find free position
Player::Player(const char* _name, Controls* _controls, int _skin, int id_):WorldPiece(0,0){
	//initialize variables
	controls=_controls;
	skin=_skin;
	name=strdup(_name);
	speed=0.01;
	type = PLAYER;
	id=id_;
	fire = 1;
	playerState = PLAYER_ALIVE;
	lives=LIVES;
}


void Player::placePlayer(int x_, int y_){
	if(x_<0 || y_<0){
		//Set random position of player		
		while((world->worldData[x=(rand()%world->worldWidth)][y=(rand()%world->worldHeight)]->type!=SPACE));
	}
	else{
		x=x_;
		y=y_;
	}

	//Set also inherited coordinates used for drawing in text mode
	_x=x;
	_y=y;

}

void Player::Die(){
	int alive=0,haveLives=0;
	playerState = PLAYER_DEATH;
	lives--;
	for(int x=0;x<game->playersCount;x++){
		if(game->players[x]->playerState==PLAYER_ALIVE)alive++;
		if(game->players[x]->lives!=0)haveLives++;
	}
	if(alive<2){
		game->gameState=STATE_STOPPED;
		drawScreen();
		//sleep(3);
		if(haveLives<2){
			game->gameState=STATE_QUIT;
		}
	}
}

bool Player::canMove(int direction){
   float dirx = directions[direction][0];
   float diry = directions[direction][1];

   int newx = roundMin(_x+dirx/2);
   int newy = roundMin(_y+diry/2);

   if(newx>=0 && newy>=0 && newx<world->worldWidth && newy<world->worldHeight)
      return ((world->worldData[newx][newy]->type<=FIRE) &&
         (world->worldData[newx][newy]->type<=FIRE));

   return false;
}
