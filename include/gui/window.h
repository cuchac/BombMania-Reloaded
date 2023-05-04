#ifndef __window__
#define __window__

#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>
//#include "RendererModules/OpenGL/CEGUIOpenGLGeometryBuffer.h"
#include "CEGUI/CEGUI.h"
//#include "CEGUI/CEGUIDefaultResourceProvider.h"

#include "gui/cegui.h"

class Window {
   public:
      Window(const char * rootName, CEGUI::Window* root);

      bool setVisibility(bool visible);
      bool isVisible();
      void activate();

   protected:
      bool visible;
      CEGUI::Window* root;
      char windowName[256];
};

#endif
