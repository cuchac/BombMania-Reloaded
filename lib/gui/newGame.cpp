#include "gui/newGame.h"
#include "game.h"
#include "settings.h"
#include "opengl/opengl.h"

#define PLAYER_STATUS_DISABLED         0
#define PLAYER_STATUS_COMPUTER         1
#define PLAYER_STATUS_HUMAN_FIRST      2
#include <controls.h>

NewGame::NewGame(const char * rootName, CEGUI::Window* rootHandle): Window(rootName, rootHandle){
   root->getChild("btnStartGame")->subscribeEvent(CEGUI::PushButton::EventClicked,  CEGUI::Event::Subscriber(&NewGame::handleStartGame, this));

   //comPlayer1Enabled, editPlayer8Name, comRounds, comMap
   char widgetName[254];

   Settings* settings = Settings::getInstance();

   // Setup Player widgets
   for(int x=0; x<MAX_PLAYERS; x++)
   {
      sprintf(widgetName, "comPlayer%dEnabled", x+1);
      CEGUI::Combobox* combo = (CEGUI::Combobox*)root->getChild(widgetName);
      
      combo->addItem(new CEGUI::ListboxTextItem("Disabled", PLAYER_STATUS_DISABLED));
      combo->addItem(new CEGUI::ListboxTextItem("Computer", PLAYER_STATUS_COMPUTER));

      for(int index = 0; index < settings->getControlsCount(); index++)
         combo->addItem(new CEGUI::ListboxTextItem(settings->getControls(index)->m_sName, PLAYER_STATUS_HUMAN_FIRST+x));

      players[x].status = combo;

      combo->setItemSelectState((size_t)0, true);
      
      sprintf(widgetName, "editPlayer%dName", x+1);
      players[x].name = (CEGUI::Editbox*)root->getChild(widgetName);
   }

   for(int x=0; x<settings->getPlayersCount(); x++)
   {
      sprintf(widgetName, "editPlayer%dName", x+1);
      root->getChild(widgetName)->setText(settings->getPlayer(x)->m_sName);

      int iControlIndex = 0;
      if((iControlIndex = settings->getControlsIndex(settings->getPlayer(x)->m_sControlsName)) >= 0)
      {
         sprintf(widgetName, "comPlayer%dEnabled", x+1);
         ((CEGUI::Combobox*)root->getChild(widgetName))->clearAllSelections();
         ((CEGUI::Combobox*)root->getChild(widgetName))->setItemSelectState(PLAYER_STATUS_HUMAN_FIRST + iControlIndex , true);
      }

   }


   // Setup Map widgets
   map = (CEGUI::Combobox*)root->getChild("comMap");

   map->addItem(new CEGUI::ListboxTextItem("default"));
   map->setItemSelectState((size_t)0, true);

   
   // Setup Round widgets
   rounds = (CEGUI::Combobox*)root->getChild("comRounds");
   rounds->addItem(new CEGUI::ListboxTextItem("1", 1));
   rounds->addItem(new CEGUI::ListboxTextItem("2", 2));
   rounds->addItem(new CEGUI::ListboxTextItem("3", 3));
   rounds->addItem(new CEGUI::ListboxTextItem("4", 4));
   rounds->addItem(new CEGUI::ListboxTextItem("5", 5));
   rounds->addItem(new CEGUI::ListboxTextItem("6", 6));
   rounds->addItem(new CEGUI::ListboxTextItem("7", 7));
   rounds->addItem(new CEGUI::ListboxTextItem("8", 8));
   rounds->addItem(new CEGUI::ListboxTextItem("9", 9));
   rounds->addItem(new CEGUI::ListboxTextItem("10", 10));

   rounds->setItemSelectState((size_t)4, true);
   
}

bool NewGame::handleStartGame(const CEGUI::EventArgs& args){
   menu->showMenu(CEGui::wNewGame, false);

   //Load new map into world
   world->loadWorld(map->getText().c_str());
   
   game = new GameOpengl();
   
   //Add one player and assign controls to that player
   Settings* settings = Settings::getInstance();
   for(int x=0; x<MAX_PLAYERS; x++)
   {
      if(players[x].status->getSelectedItem()->getID()>PLAYER_STATUS_COMPUTER)
         game->AddPlayer(players[0].name->getText().c_str(),settings->getControls(players[x].status->getText().c_str()),x);
   }

   settings->save();

   startGame();
   return true;
}

bool NewGame::clearEditBox(const CEGUI::EventArgs& args){
   /*if(!args.handled){
      root->getChild("editPlayer1Name")->setText("");
   }*/
   //root->getChild("editPlayer1Name")->unsubscribeEvent(CEGUI::PushButton::EventActivated);
   return true;
}