#ifndef __loader__
#define __loader__

#include <map>
#include "objectLoader/object.h"
#include "objectLoader/3dsloader.h"
#include <string.h>

class ObjectLoader {

   public:
      ObjectLoader(){};
      static bool LoadObject(const char * objectName);
      static bool LoadTexture(const char * textureName);
      static bool LoadModel(const char * modelName);

   protected:
      struct ltstr
      {
         bool operator()(const char* s1, const char* s2) const
         {
            return strcmp(s1, s2) < 0;
         }
      };
      
      typedef std::map<const char *, OpenglModel *, ltstr> objectMap;
      typedef std::map<const char *, obj_type *, ltstr> modelMap;
      typedef std::map<const char *, GLuint, ltstr> textureMap;

      static objectMap objects;
      static textureMap textures;
      static modelMap models;

};





#endif
