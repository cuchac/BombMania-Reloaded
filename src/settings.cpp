/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "settings.h"
#include "limits.h"
#include "support.h"
#include <string.h>
#include <xml/xml.h>
#include <controls.h>

#include <GL/glut.h>

Settings* Settings::m_pInstance = NULL;
std::string Settings::s_sExeDir = "./";

Settings::Settings()
{
}

bool Settings::load()
{
   char homeDir[PATH_MAX];

   getHomeDir(homeDir);

   Xml xmlFile;
   if(xmlFile.load(homeDir, ".bombmania", "conf"))
   {
      TiXmlElement* pElem;
      TiXmlElement* root = xmlFile.getRoot();

      pElem = root->FirstChild("Controls")->FirstChildElement();
      for(; pElem; pElem = pElem->NextSiblingElement())
      {
         const char * name = pElem->Attribute("name");
         
         if(strcmp(pElem->Attribute("type"), "keyboard") == 0)
         {
            ControlsKeyboard * tmp = new ControlsKeyboard(name);
            tmp->load(pElem);
            m_controls.push_back(tmp);
         }
         else
            printf("Unknown input type: %s\n", pElem->Attribute("type"));
      }

      pElem = root->FirstChild("Players")->FirstChildElement();
      for(; pElem; pElem = pElem->NextSiblingElement())
      {
         PlayerSettings tmp;
         strncpy(tmp.m_sName, pElem->Attribute("name"), MAX_NAME_LEN);
         strncpy(tmp.m_sControlsName, pElem->Attribute("controls"), MAX_NAME_LEN);

         if(getControls(tmp.m_sControlsName) == NULL)
            tmp.m_sControlsName[0] = 0;
         
         m_players.push_back(tmp);
      }
      
   }
   else
   {
      printf("Config file \"%s/%s\"not found. Loading default settings.\n", homeDir, ".bombmania.conf");

      PlayerSettings tmpPlayer;
      strncpy(tmpPlayer.m_sName, "Joe", MAX_NAME_LEN);
      strncpy(tmpPlayer.m_sControlsName, "Keyboard 1", MAX_NAME_LEN);
      m_players.push_back(tmpPlayer);

      strncpy(tmpPlayer.m_sName, "KOPRajs", MAX_NAME_LEN);
      strncpy(tmpPlayer.m_sControlsName, "Keyboard 2", MAX_NAME_LEN);
      m_players.push_back(tmpPlayer);

      
      //Set controls. Also should be called from init's menu
      ControlsKeyboard *tmp = new ControlsKeyboard("Keyboard 1");
      tmp->m_down=0xFF+GLUT_KEY_UP;
      tmp->m_up=0xFF+GLUT_KEY_DOWN;
      tmp->m_left=0xFF+GLUT_KEY_LEFT;
      tmp->m_right=0xFF+GLUT_KEY_RIGHT;
      tmp->m_plant=13;

      m_controls.push_back(tmp);

      
      tmp = new ControlsKeyboard("Keyboard 2");
      tmp->m_down='w';
      tmp->m_up='s';
      tmp->m_left='a';
      tmp->m_right='d';
      tmp->m_plant='q';
      
      m_controls.push_back(tmp);
      
   }

   return true;
}

bool Settings::save()
{
   Xml xmlFile;
   xmlFile.createEmptyRoot("Settings");
   
   TiXmlElement* pElem;
   TiXmlElement* root = xmlFile.getRoot();

   pElem = root->InsertEndChild(TiXmlElement("Controls"))->ToElement();

   for(uint x=0; x<m_controls.size(); x++)
   {
      TiXmlElement tmp("Controler");
      tmp.SetAttribute("name", m_controls[x]->m_sName);
      tmp.SetAttribute("type", "keyboard");

      ((ControlsKeyboard*)m_controls[x])->save(&tmp);
      
      pElem->InsertEndChild(tmp);
   }

   pElem = root->InsertEndChild(TiXmlElement("Players"))->ToElement();

   for(uint x=0; x<m_players.size(); x++)
   {
      TiXmlElement tmp("Player");
      tmp.SetAttribute("name", m_players[x].m_sName);
      tmp.SetAttribute("controls", m_players[x].m_sControlsName);
      pElem->InsertEndChild(tmp);
   }


   char homeDir[PATH_MAX];

   getHomeDir(homeDir);

   if(xmlFile.save(homeDir, ".bombmania", "conf"))
   {
      printf("Settings saved to config file \"%s/%s\"!\n", homeDir, ".bombmania.conf");
   }
   else
   {
      printf("Canot save config file \"%s/%s\"!\n", homeDir, ".bombmania.conf");
   }
   
   return true;
}

int Settings::getPlayersCount()
{
   return m_players.size();
}

Settings::PlayerSettings* Settings::getPlayer(int index)
{
   return &m_players[index];
}


int Settings::getControlsCount()
{
   return m_controls.size();
}

Controls* Settings::getControls(int index)
{
   return m_controls[index];
}

int Settings::getControlsIndex(const char * name)
{
   for(unsigned int x=0; x<m_controls.size(); x++)
   {
      if(strcmp(name, m_controls[x]->m_sName))
         return x;
   }

   printf("Cannot find controls \"%s\"\n", name);
   
   return 0;
}

Controls* Settings::getControls(const char * name)
{
   int index = getControlsIndex(name);

   if(index < 0)
   {
      printf("Cannot find controls \"%s\"\n", name);
      return NULL;
   }
   else
      return m_controls[index];
}

Settings* Settings::getInstance()
{
   if(m_pInstance)
      return m_pInstance;

   m_pInstance = new Settings;
   m_pInstance->load();

   return m_pInstance;
}
