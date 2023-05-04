#ifndef __ingameMenu__
#define __ingameMenu__

#include "gui/cegui.h"
#include "gui/window.h"

class IngameMenu : public Window {
   public:
      IngameMenu(const char * rootName, CEGUI::Window* root);

   private:
      bool handleResumeGame(const CEGUI::EventArgs& args);
      bool handleExitGame(const CEGUI::EventArgs& args);
};

#endif
