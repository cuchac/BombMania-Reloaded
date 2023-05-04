#ifndef CONTROLS_H
#define CONTROLS_H

#include "settings.h"

class TiXmlElement;

#define KEY_UP       0x01
#define KEY_RIGHT    0x02
#define KEY_DOWN     0x04
#define KEY_LEFT     0x08

#define KEY_PLANT    0x10

//Stores keycodes for every player action, this would be hopefuly set in in-game setup
class Controls{
   public:
                     Controls(const char * name);

      bool           load(TiXmlElement* from);
      bool           save(TiXmlElement* to);

   public:
      int            m_iType;
      char           m_sName[MAX_NAME_LEN];
      
};

class ControlsKeyboard : public Controls{
   public:
                     ControlsKeyboard(const char * name);
                     
      bool           load(TiXmlElement* from);
      bool           save(TiXmlElement* to);

      bool           handleInput(int key, bool bKeyDown, int * keyPressed);
      
   public:
      int         m_up;
      int         m_down;
      int         m_left;
      int         m_right;
      int         m_plant;
};

#endif // CONTROLS_H
