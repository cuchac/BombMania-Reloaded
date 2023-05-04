#ifndef __loading__
#define __loading__

#include "gui/cegui.h"
#include "gui/window.h"

class Loading : public Window {
   public:
      Loading(const char * rootName, CEGUI::Window* root): Window(rootName, root),stepSize(0){};
      static void onLoading(void);
      static void drawFrame(void);

   private:
      void setRange(int range);
      void step();
      float stepSize;
};

#endif
