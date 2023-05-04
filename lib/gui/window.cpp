#include "gui/cegui.h"
#include "gui/window.h"

Window::Window(const char * rootName, CEGUI::Window* rootHandle){
   strcpy(windowName, rootName);
   
   this->root = rootHandle->getChild(rootName);
   
   this->setVisibility(false);
}

bool Window::setVisibility(bool visible){
   this->visible = visible;
   root->setVisible(visible);
   return true;
}

bool Window::isVisible(){
   return this->visible;
}

void Window::activate(){
   this->root->activate();
}