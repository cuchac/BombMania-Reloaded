#include <stdlib.h>
#include "bombmania.h"
#include "gui/cegui.h"
#include "gui/mainmenu.h"
#include "gui/loading.h"
#include "gui/ingameMenu.h"
#include "gui/newGame.h"
#include "gui/messageBox.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

CEGui *menu;

int CEGui::modifiers=0;
int CEGui::lastFrameTime=0;
int CEGui::fps_lastTime=0;
int CEGui::fps_frames=0;
int CEGui::fps_value=0;
int CEGui::displayedWindows=0;
char CEGui::fps_textbuff[16];

CEGui::CEGui(){
   glutSetCursor(GLUT_CURSOR_NONE);

   renderer = &CEGUI::OpenGLRenderer::bootstrapSystem();

    // initialise the required dirs for the DefaultResourceProvider
   auto rp = dynamic_cast<CEGUI::DefaultResourceProvider*>
         (CEGUI::System::getSingleton().getResourceProvider());

   auto dataPath = strdup(CREATE_PATH(GUI_PATH));
   rp->setResourceGroupDirectory("schemes", dataPath);
   rp->setResourceGroupDirectory("imagesets", dataPath);
   rp->setResourceGroupDirectory("fonts", dataPath);
   rp->setResourceGroupDirectory("layouts", dataPath);
   rp->setResourceGroupDirectory("looknfeels", dataPath);
   rp->setResourceGroupDirectory("lua_scripts", dataPath);
   free(dataPath);

   CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
   CEGUI::Font::setDefaultResourceGroup("fonts");
   CEGUI::Scheme::setDefaultResourceGroup("schemes");
   CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
   CEGUI::WindowManager::setDefaultResourceGroup("layouts");
   CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

   // load in the scheme file, which auto-loads the TaharezLook imageset
   CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");

   CEGUI::Window* root = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("bombmania.layout");
   CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(root);

   CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

   displayedWindows = 0;

   this->windows[wMainMenu] = new MainMenu("winMainMenu", root);
   this->windows[wLoading] = new Loading("winLoadingScreen", root);
   this->windows[wIngameMenu] = new IngameMenu("winInGameMenu", root);
   this->windows[wNewGame] = new NewGame("winNewGame", root);
   this->windows[wMessageBox] = new MessageBox("winMessage", root);
}

CEGui::~CEGui(){
   CEGUI::OpenGLRenderer::destroySystem();
}

bool CEGui::showMenu(enum windowName window, bool bShow){
   // set starting time
   fps_lastTime = lastFrameTime = glutGet(GLUT_ELAPSED_TIME);

   if(window < CEGui::wLAST){
      if(bShow){
         if(!this->windows[window]->isVisible())
            displayedWindows++;
      }else{
         if(this->windows[window]->isVisible())
            displayedWindows--;
      }

      this->windows[window]->setVisibility(bShow);
   }

   return false;
}

bool CEGui::isVisible(enum windowName window){
   return this->windows[window]->isVisible();
}

void CEGui::drawFrame(){
   CEGUI::System& guiSystem = CEGUI::System::getSingleton();
    // do time based updates
   int thisTime = glutGet(GLUT_ELAPSED_TIME);
   float elapsed = static_cast<float>(thisTime - lastFrameTime);
   lastFrameTime = thisTime;
   // inject the time pulse
   
   guiSystem.injectTimePulse(elapsed / 1000.0f);
   // update fps fields
   doFPSUpdate();

   guiSystem.renderAllGUIContexts();

   // render FPS:
   CEGUI::Font* fnt = guiSystem.getDefaultGUIContext().getDefaultFont();
   if (fnt)
   {
      //guiSystem.getRenderer()->setQueueingEnabled(false);
      //fnt->drawText(fps_textbuff, CEGUI::Vector3f(0, 0, 0), guiSystem.getRenderer()->getRect());
   }
}

void CEGui::reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(45.0, (GLfloat) w/(GLfloat) h, 0.1, 100.0);
   glMatrixMode(GL_MODELVIEW);
   auto* renderer = CEGUI::System::getSingleton().getRenderer();
   renderer->setDisplaySize(CEGUI::Sizef((float)w,(float)h));
}

void CEGui::mouseMotion(int x, int y)
{
   CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(x, y);
}

bool CEGui::mouseButton(int button, int state, int x, int y)
{
   if(CEGui::displayedWindows == 0)
      return false;
   
   auto context = CEGUI::System::getSingleton().getDefaultGUIContext();
   
   switch(button)
   {
      case  GLUT_LEFT_BUTTON:
         if (state == GLUT_UP)
         {
            context.injectMouseButtonUp(CEGUI::LeftButton);
         }
         else
         {
            context.injectMouseButtonDown(CEGUI::LeftButton);

         }
         break;

      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_UP)
         {
            context.injectMouseButtonUp(CEGUI::RightButton);
         }
         else
         {
            context.injectMouseButtonDown(CEGUI::RightButton);
         }
         break;

      case GLUT_MIDDLE_BUTTON:
         if (state == GLUT_UP)
         {
            context.injectMouseButtonUp(CEGUI::MiddleButton);
         }
         else
         {
            context.injectMouseButtonDown(CEGUI::MiddleButton);
         }
         break;
   }
   
   return true;

}

bool CEGui::keyChar(unsigned char key, int x, int y)
{
   if(CEGui::displayedWindows == 0)
      return false;
   
   auto context = CEGUI::System::getSingleton().getDefaultGUIContext();
   
   handleModifierKeys();

    // extract some keys may be handled via key code and generate those too
   switch (key)
   {
      case 0x08:  // backspace
         context.injectKeyDown(CEGUI::Key::Backspace);
         break;
      case 0x7F:  // delete
         context.injectKeyDown(CEGUI::Key::Delete);
         break;
      case 0x1B:  // Escape
         //d_quitFlag = true;
         break;
      case 0x0D:  // CR (Return)
         context.injectKeyDown(CEGUI::Key::Return);
         break;
      default:
        // inject Character code
         context.injectChar(static_cast<CEGUI::utf32>(key));
         break;
   }
   return true;
}

bool CEGui::keySpecial(int key, int x, int y)
{
   if(CEGui::displayedWindows == 0)
      return false;
   
   handleModifierKeys();
   
   auto context = CEGUI::System::getSingleton().getDefaultGUIContext();

   GlutKeyMapping* mapping = specialKeyMap;

   while (mapping->glutKey != -1)
   {
      if (mapping->glutKey == key)
      {
         context.injectKeyDown((CEGUI::Key::Scan)mapping->ceguiKey);
         return true;
      }

      ++mapping;
   }
   return true;
}

bool CEGui::handleModifierKeys(void)
{
   int mods = glutGetModifiers();

   CEGUI::System& cesys = CEGUI::System::getSingleton();

   bool shift = mods&GLUT_ACTIVE_SHIFT;
   bool ctrl  = mods&GLUT_ACTIVE_CTRL;
   bool alt   = mods&GLUT_ACTIVE_ALT;
   
   auto context = CEGUI::System::getSingleton().getDefaultGUIContext();

    // shift
   if (shift != bool(modifiers&GLUT_ACTIVE_SHIFT))
   {
      CEGUI::Key::Scan sc = CEGUI::Key::LeftShift;
      if(shift)
      {
         context.injectKeyDown(sc);
      }
      else
      {
         context.injectKeyUp(sc);
      }
   }
 // control
   if (ctrl != bool(modifiers&GLUT_ACTIVE_CTRL))
   {
      CEGUI::Key::Scan sc = CEGUI::Key::LeftControl;
      if (shift)
      {
         context.injectKeyDown(sc);
      }
      else
      {
         context.injectKeyUp(sc);
      }
   }

    // alt
   if (alt != bool(modifiers&GLUT_ACTIVE_ALT))
   {
      CEGUI::Key::Scan sc = CEGUI::Key::LeftAlt;
      if (shift)
      {
         context.injectKeyDown(sc);
      }
      else
      {
         context.injectKeyUp(sc);
      }
   }

   modifiers = mods;
   
   return true;
}

void CEGui::doFPSUpdate()
{
    // another frame
   ++fps_frames;

    // has at least a second passed since we last updated the text?
   if (lastFrameTime - fps_lastTime >= 1000)
   {
        // update FPS text to output
      sprintf(fps_textbuff , "FPS: %d", fps_frames);
        // reset counter
      fps_frames    = 0;
        // update timer
      fps_lastTime  = lastFrameTime;
   }
}

void CEGui::showLoadingScreen(){
   showMenu(wLoading);
   glutDisplayFunc(Loading::onLoading);
}


void CEGui::messageBox(const char * message){
   ((MessageBox*)(windows[wMessageBox]))->setText(message);
   showMenu(wMessageBox, true);
   windows[wMessageBox]->activate();
}

void CEGui::setFocus(enum windowName window){
   windows[window]->activate();
}
