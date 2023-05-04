#include "xml/xml.h"
#include "limits.h"
#include "sys/stat.h"

bool Xml::load(const char* directory, const char* filename, const char* fileExt)
{
   if(!filename)
      return false;

   char filePath[PATH_MAX];

   sprintf(filePath, "%s/%s.%s", directory, filename, fileExt);

   bool loadOkay = xmlDoc.LoadFile(filePath);
   if(!loadOkay){
      printf("Cannot open XML file '%s', Error Row:%d Col:%d - %s\n", filePath, xmlDoc.ErrorRow(), xmlDoc.ErrorCol(), xmlDoc.ErrorDesc());
      return false;
   }

   return true;

};

bool Xml::save(const char* directory, const char* filename, const char* fileExt)
{
   if(!filename)
      return false;
   
   char filePath[PATH_MAX];
   
   sprintf(filePath, "%s/%s.%s", directory, filename, fileExt);
   
   bool saveOkay = xmlDoc.SaveFile(filePath);
   if(!saveOkay){
      printf("Cannot save XML file '%s', Error Row:%d Col:%d - %s\n", filePath, xmlDoc.ErrorRow(), xmlDoc.ErrorCol(), xmlDoc.ErrorDesc());
      return false;
   }
   
   return true;
   
};

TiXmlElement* Xml::getRoot()
{
   return xmlDoc.RootElement();
};

TiXmlElement* Xml::createEmptyRoot(const char* name)
{
   xmlDoc.ClearError();
   xmlDoc.Clear();
   xmlDoc.InsertEndChild(TiXmlDeclaration( "1.0", "", "" ));
   xmlDoc.InsertEndChild(TiXmlElement(name));
   return xmlDoc.RootElement();
}