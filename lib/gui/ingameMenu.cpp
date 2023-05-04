#include "gui/ingameMenu.h"
#include "game.h"
#include "opengl/opengl.h"


IngameMenu::IngameMenu(const char * rootName, CEGUI::Window* rootHandle): Window(rootName, rootHandle){
   root->getChild("btn_gResumeGame")->subscribeEvent(CEGUI::PushButton::EventClicked,  CEGUI::Event::Subscriber(&IngameMenu::handleResumeGame, this));
   root->getChild("btn_gEndGame")->subscribeEvent(CEGUI::PushButton::EventClicked,  CEGUI::Event::Subscriber(&IngameMenu::handleExitGame, this));
}

bool IngameMenu::handleResumeGame(const CEGUI::EventArgs& args){
   menu->showMenu(CEGui::wIngameMenu, false);
   return true;
}

bool IngameMenu::handleExitGame(const CEGUI::EventArgs& args){
   exit(0);
   return true;
}
