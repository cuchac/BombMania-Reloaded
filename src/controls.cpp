#include "controls.h"
#include "settings.h"
#include "player.h"
#include <xml/xml.h>

Controls::Controls(const char * name)
{
   strncpy(m_sName, name, MAX_NAME_LEN);
}

ControlsKeyboard::ControlsKeyboard(const char * name):Controls(name)
{
   m_iType = CONTROLS_TYPE_KEYBOARD;
}

bool ControlsKeyboard::load(TiXmlElement* from)
{
   m_up = atoi(from->FirstChildElement("up")->Attribute("key"));
   m_down = atoi(from->FirstChildElement("down")->Attribute("key"));
   m_left = atoi(from->FirstChildElement("left")->Attribute("key"));
   m_right = atoi(from->FirstChildElement("right")->Attribute("key"));
   m_plant = atoi(from->FirstChildElement("plant")->Attribute("key"));

   return true;
}

bool ControlsKeyboard::save(TiXmlElement* to)
{
   to->Clear();
   to->SetAttribute("type", "keyboard");
   to->InsertEndChild(TiXmlElement("up"));
   to->InsertEndChild(TiXmlElement("down"));
   to->InsertEndChild(TiXmlElement("left"));
   to->InsertEndChild(TiXmlElement("right"));
   to->InsertEndChild(TiXmlElement("plant"));

   to->FirstChildElement("up")->SetAttribute("key", m_up);
   to->FirstChildElement("down")->SetAttribute("key", m_down);
   to->FirstChildElement("left")->SetAttribute("key", m_left);
   to->FirstChildElement("right")->SetAttribute("key", m_right);
   to->FirstChildElement("plant")->SetAttribute("key", m_plant);

   return true;
}

bool ControlsKeyboard::handleInput(int key, bool bKeyDown, int* keyPressed)
{
   if(key==m_left)
      (bKeyDown)?*keyPressed|=KEY_LEFT:*keyPressed&=~KEY_LEFT;
   else if(key==m_right)
      (bKeyDown)?*keyPressed|=KEY_RIGHT:*keyPressed&=~KEY_RIGHT;
   else if(key==m_up)
      (bKeyDown)?*keyPressed|=KEY_UP:*keyPressed&=~KEY_UP;
   else if(key==m_down)
      (bKeyDown)?*keyPressed|=KEY_DOWN:*keyPressed&=~KEY_DOWN;
   else if(key==m_plant)
      (bKeyDown)?*keyPressed|=KEY_PLANT:*keyPressed&=~KEY_PLANT;
   else return false;
   return true;
}