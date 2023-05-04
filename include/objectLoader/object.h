#ifndef _OBJECT_H
#define _OBJECT_H

#include "world.h"
#include "objectLoader/3dsloader.h"

class OpenglModel {
   public:
      OpenglModel(const char * modelName);
      virtual void draw();
   private:
      char *name;
      obj_type * object;
      GLuint texture;
      GLuint list;
   
};

#endif
