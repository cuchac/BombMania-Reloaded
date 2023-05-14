#ifndef __cegui__
#define __cegui__

//#include <GL/glut.h>
//#include <GL/gl.h>
//#include <GL/glu.h>

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>

class Window;


/*************************************************************************
    Simple key-map used to translate glut special keys to CEGUI keys.
    See: CEGuiOpenGLBaseApplication::keySpecial method.
*************************************************************************/
struct GlutKeyMapping
{
   int glutKey;
   unsigned int  ceguiKey;
};

extern GlutKeyMapping specialKeyMap[];

class CEGui {
   public:
      enum windowName{
         wMainMenu,
         wLoading,
         wSettings,
         wStats,
         wIngameMenu,
         wNewGame,
         wMessageBox,
         wLAST
      };

   public:
      CEGui();
      ~CEGui();

      bool showMenu(enum windowName window, bool bShow = true);
      bool isVisible(enum windowName window);
      void showLoadingScreen();
      void messageBox(const char * message);
      void setFocus(enum windowName window);
      
      void drawFrame();

      static void mouseMotion(int x, int y);
      static bool mouseButton(int button, int state, int x, int y);
      static bool keyChar(unsigned char key, int x, int y);
      static bool keySpecial(int key, int x, int y);
      static bool handleModifierKeys(void);
      static void handleMouseWheel_freeglut(int wheel, int dir, int x, int y);
      static void reshape(int w, int h);

      Window* windows[wLAST];

   private:

      static void doFPSUpdate();

      CEGUI::OpenGLRenderer* renderer;

      static int modifiers;
      static int displayedWindows;

      // FPS stuff
      static int lastFrameTime;
      static int fps_lastTime;
      static int fps_frames;
      static int fps_value;
      static char fps_textbuff[16];


};

extern CEGui *menu;

#endif
