#include "objectLoader/loader.h"

void OpenglModel::draw()
{

   /*glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   glTranslatef(x, y, z);

   glRotatef(rotz, 0.0f, 0.0f, 1.0f);
   glRotatef(rotx, 1.0f, 0.0f, 0.0f);
   glRotatef(roty, 0.0f, 1.0f, 0.0f);
    

   glScalef(scale,scale,scale);

   glCallList(object);
    
   glPopMatrix();*/
 
}

OpenglModel::OpenglModel(const char * modelName){
   name = new char[strlen(modelName)+1];
   
   strcpy(name, modelName);
}
