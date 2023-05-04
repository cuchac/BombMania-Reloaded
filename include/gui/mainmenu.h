#ifndef __mainmenu__
#define __mainmenu__
#include "gui/cegui.h"
#include "gui/window.h"

class MainMenu : public Window {
   public:
      MainMenu(const char * rootName, CEGUI::Window* root);

   private:
      bool handleNewGame(const CEGUI::EventArgs& args);
      bool handleExitGame(const CEGUI::EventArgs& args);
};

#endif
