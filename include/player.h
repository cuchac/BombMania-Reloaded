#ifndef PLAYER_H_
#define PLAYER_H_

#include "world.h"

class Controls;

//Defines for directions used in move()
#define UP 	0
#define RIGHT	1
#define DOWN	2
#define LEFT  	3

extern int directions[4][3];

#define PLAYER_ALIVE	1
#define PLAYER_DEATH	2
#define PLAYER_OUT	3
#define GAME_OVER	4

//Threashold the tolerance of float position in the matrix of World
//0.01 is anough to handle 0.02 steps (speed). Generaly must be smaller than speed
#define THREASHOLD 0.01

//Support functions.
//#define round(a) int(a + 0.5) //Simple (but powerfull :)) round function
#define roundMin(a) int(a + 0.5 - THREASHOLD) // These two functions is for THREASHOLD implementation. Necesary because of floating point error
#define roundMax(a) int(a + 0.5 + THREASHOLD)

//Player Class .... inherits from WorldPiece for drawing posibility
class Player : public WorldPiece{
   public:
                     Player(const char * _name, Controls* _controls, int skin, int id);

   public:
      virtual bool   handleKey(int key);
      virtual void   plantBomb();
      
      virtual void   move(float dx, float dy);
      
      virtual void   Draw();
      virtual void   Destroy();
      virtual void   placePlayer(int x, int y);
      virtual void   Die();

   protected:
      bool           canMove(int direction);
      
	public:
		float          _x,_y;
		char *         name;
		int            skin, id, playerState, lives;	
		int            fire;
		float          speed;
		Controls*      controls;

};


#endif /*PLAYER_H_*/

