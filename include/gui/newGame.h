#ifndef __newGame__
#define __newGame__

#include "gui/cegui.h"
#include "gui/window.h"
#include "game.h"

class NewGame : public Window {
   public:
      NewGame(const char * rootName, CEGUI::Window* root);

   private:
      bool              handleStartGame(const CEGUI::EventArgs& args);
      bool              clearEditBox(const CEGUI::EventArgs& args);
      //bool              handleExitGame(const CEGUI::EventArgs& args);

   private:

      typedef struct playerWidget_t {
         CEGUI::Combobox* status;
         CEGUI::Editbox * name;
      } playerWidget;

      
      playerWidget      players[MAX_PLAYERS];
      CEGUI::Combobox*  map;
      CEGUI::Combobox*  rounds;
};

#endif
