#include "sys/stat.h"
#include "limits.h"

#include "bombmania.h"
#include "objectLoader/loader.h"
#include "objectLoader/texture.h"
#include "xml/xml.h"

ObjectLoader::objectMap ObjectLoader::objects;
ObjectLoader::textureMap ObjectLoader::textures;
ObjectLoader::modelMap ObjectLoader::models;

bool ObjectLoader::LoadObject(const char * objectName){
   //If object allready exists
   if(objects.find(objectName) != objects.end())
      return true;
   
   Xml xmlFile;
   if(!xmlFile.load(CREATE_PATH(OBJECTS_PATH), objectName))
      return false;
   
   TiXmlElement* xmlRoot = xmlFile.getRoot();
   
   OpenglModel *temp = new OpenglModel(objectName);
   objects[objectName] = temp;
   
   TiXmlElement * pElem = xmlRoot->FirstChildElement("textures")->FirstChildElement();
   for( ; pElem; pElem=pElem->NextSiblingElement())
      LoadTexture(pElem->Attribute("filename"));

   pElem = xmlRoot->FirstChildElement("models")->FirstChildElement();
   for( ; pElem; pElem=pElem->NextSiblingElement())
      LoadModel(pElem->Attribute("filename"));

   return true;
}

bool ObjectLoader::LoadTexture(const char * textureName){
   if(!textureName)return false;
   
   char filePath[PATH_MAX];
   sprintf(filePath, "%s%s", CREATE_PATH(TEXTURES_PATH), textureName);
   return ::LoadTexture(filePath);
}

bool ObjectLoader::LoadModel(const char * modelName){
   return false;
}
