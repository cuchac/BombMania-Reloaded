#include "bombmania.h"
#include "gui/loading.h"
#include "opengl/opengl.h"

void Loading::setRange(int range){
   stepSize = 1.0f/(double)range;
   ((CEGUI::ProgressBar*)root->getChild("barProgress"))->setStepSize(stepSize);
}

void Loading::step(){
   ((CEGUI::ProgressBar*)root->getChild("barProgress"))->step();
}

void Loading::onLoading()
{

   ((Loading*)menu->windows[CEGui::wLoading])->setRange(11);
   Loading::drawFrame();

   ObjLoad(&ship01, CREATE_PATH(MODELS_PATH "fighter01.3ds"), CREATE_PATH(TEXTURES_PATH "fighter01.bmp"));
   ((Loading*)menu->windows[CEGui::wLoading])->step();
   Loading::drawFrame();
   ObjLoad(&ship02, CREATE_PATH(MODELS_PATH "fighter02.3ds"), CREATE_PATH(TEXTURES_PATH "fighter02.bmp"));
   ((Loading*)menu->windows[CEGui::wLoading])->step();
   Loading::drawFrame();
   ObjLoad(&mine, CREATE_PATH(MODELS_PATH "mine.3ds"), CREATE_PATH(TEXTURES_PATH "mine.bmp"));
   ((Loading*)menu->windows[CEGui::wLoading])->step();
   Loading::drawFrame();
   ObjLoad(&asteroid01, CREATE_PATH(MODELS_PATH "asteroid01.3ds"), CREATE_PATH(TEXTURES_PATH "asteroid01.bmp"));
   ((Loading*)menu->windows[CEGui::wLoading])->step();
   Loading::drawFrame();
   ObjLoad(&asteroid02, CREATE_PATH(MODELS_PATH "asteroid02.3ds"), CREATE_PATH(TEXTURES_PATH "asteroid02.bmp"));
   ((Loading*)menu->windows[CEGui::wLoading])->step();
   Loading::drawFrame();
   ObjLoad(&asteroid03, CREATE_PATH(MODELS_PATH "asteroid03.3ds"), CREATE_PATH(TEXTURES_PATH "asteroid03.bmp"));
   ((Loading*)menu->windows[CEGui::wLoading])->step();
   Loading::drawFrame();
   LoadExplosion(&explosion, CREATE_PATH(TEXTURES_PATH "wave.bmp"));
   ((Loading*)menu->windows[CEGui::wLoading])->step();
   Loading::drawFrame();
   LoadExplosion(&explosionRed, CREATE_PATH(TEXTURES_PATH "waveRed.png"));
   ((Loading*)menu->windows[CEGui::wLoading])->step();
   Loading::drawFrame();
   LoadExplosion(&explosionSun, CREATE_PATH(TEXTURES_PATH "waveSun.png"));
   ((Loading*)menu->windows[CEGui::wLoading])->step();
   Loading::drawFrame();
   ObjLoad(&background, CREATE_PATH(MODELS_PATH "stars.3ds"), CREATE_PATH(TEXTURES_PATH "stars.png"));
   ((Loading*)menu->windows[CEGui::wLoading])->step();
   Loading::drawFrame();
   ObjLoad(&jupiter, CREATE_PATH(MODELS_PATH "sphere.3ds"), CREATE_PATH(TEXTURES_PATH "jupitermap.png"));
   ((Loading*)menu->windows[CEGui::wLoading])->step();
   Loading::drawFrame();

   menu->showMenu(CEGui::wMainMenu, true);
   menu->showMenu(CEGui::wLoading, false);

   glutDisplayFunc(onDisplay);
   glutKeyboardFunc(onKeyboard);
   glutKeyboardUpFunc(onKeyboardUp);
   glutSpecialFunc(onSpecial);
   glutSpecialUpFunc(onSpecialUp);
   glutIdleFunc(onIddle);
   glutMouseFunc(onMouse);
   glutMotionFunc(onMotion);
   glutPassiveMotionFunc(onMotion);
}

void Loading::drawFrame()
{
   CEGUI::System& guiSystem = CEGUI::System::getSingleton();

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   setCamera();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);

    guiSystem.renderAllGUIContexts();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

   glFlush();
   glutSwapBuffers();
   //glutPostRedisplay();
}
