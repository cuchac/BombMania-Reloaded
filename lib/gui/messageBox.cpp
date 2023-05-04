#include <stdlib.h>
#include "gui/messageBox.h"
#include "game.h"
#include "opengl/opengl.h"


MessageBox::MessageBox(const char * rootName, CEGUI::Window* rootHandle): Window(rootName, rootHandle){
   textMessage = root->getChild("textMessage");
}

bool MessageBox::setText(const char * message){
   textMessage->setText (message);
   
   return true;
}