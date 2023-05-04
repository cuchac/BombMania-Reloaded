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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <vector>
#include <string>

#define MAX_NAME_LEN             50

#define CONTROLS_TYPE_KEYBOARD         1
#define CONTROLS_TYPE_MOUSE            2
#define CONTROLS_TYPE_ACCELEROMETER    3

class Controls;

class Settings
{
   public:
                        Settings();

   public:
      bool              load();
      bool              save();

   public:
      typedef struct PlayerSettings_t {
         char     m_sName[MAX_NAME_LEN];
         char     m_sControlsName[MAX_NAME_LEN];
      } PlayerSettings;
      
      typedef std::vector<PlayerSettings> PlayersList;
      typedef std::vector<Controls*> ControlsList;

   public:
      int               getPlayersCount();
      PlayerSettings*   getPlayer(int index);

      int               getControlsCount();
      Controls*         getControls(int index);
      int               getControlsIndex(const char* name);
      Controls*         getControls(const char* name);
      
      static Settings*  getInstance();
      
   public:
      static std::string s_sExeDir;

   private:
      PlayersList       m_players;
      ControlsList      m_controls;
      static Settings*  m_pInstance;
      
};

#endif // SETTINGS_H
