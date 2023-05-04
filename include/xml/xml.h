#ifndef __XML_H__
#define __XML_H__

#ifndef TIXML_USE_STL
   #define TIXML_USE_STL
#endif

#include "xml/tinyxml.h"

class Xml
{
   public:
      bool           load(const char * directory, const char * filename, const char * fileExt = "xml");
      bool           save(const char * directory, const char * filename, const char * fileExt = "xml");

   public:
      TiXmlElement*  getRoot();
      TiXmlElement*  createEmptyRoot(const char* name);

   private:
      TiXmlDocument  xmlDoc;
};

#endif // __XML_H__
