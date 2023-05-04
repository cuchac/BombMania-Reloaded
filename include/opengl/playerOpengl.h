#ifndef __playerOpengl__
#define __playerOpengl__

#include "player.h"

#define ROT_LEFT 90
#define ROT_RIGHT 270
#define ROT_UP 180
#define ROT_DOWN 0

//Define player FLAGS
//#define PLAYER_FLAG_ROTATING 0x0001

class PlayerOpengl : public Player{
   public:

      PlayerOpengl(const char* _name, Controls* _controls, int skin, int id);

      //Input handling
      virtual bool setPressedKey(int key, bool keyPressed);
      virtual void processEvents();

      //Movement functions
      virtual void move(float dx, float dy);
      virtual void rotate(int degree);
      virtual int getRotDif(int angle1, int angle2);
      
      //Player actions
      virtual void plantBomb();
      virtual void Die();

      int keyPressed;
      float accel;
      float actionTime;
      int rotateDirection;
      int flags;
};

#endif
