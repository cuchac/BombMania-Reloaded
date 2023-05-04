#ifndef __messageBox__
#define __messageBox__

#include "gui/cegui.h"
#include "gui/window.h"

class MessageBox : public Window {
   CEGUI::Window* textMessage;
   public:
      MessageBox(const char * rootName, CEGUI::Window* root);
      bool setText(const char * message);
      //bool handleExitGame(const CEGUI::EventArgs& args);
};


#endif
