#include "gui/mainmenu.h"
#include "game.h"
#include "opengl/opengl.h"


MainMenu::MainMenu(const char * rootName, CEGUI::Window* rootHandle): Window(rootName, rootHandle){
   root->getChild("btnNewGame")->subscribeEvent(CEGUI::PushButton::EventClicked,  CEGUI::Event::Subscriber(&MainMenu::handleNewGame, this));
   root->getChild("btnExitGame")->subscribeEvent(CEGUI::PushButton::EventClicked,  CEGUI::Event::Subscriber(&MainMenu::handleExitGame, this));
}

bool MainMenu::handleNewGame(const CEGUI::EventArgs& args){
   menu->showMenu(CEGui::wNewGame, true);
   menu->setFocus(CEGui::wNewGame);
   return true;
}

bool MainMenu::handleExitGame(const CEGUI::EventArgs& args){
   exit(0);
   return true;
}
