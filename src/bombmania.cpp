#include <cstdio>
#include <cstdlib>

#include "bombmania.h"
#include "module.h"
#include "settings.h"

int main(int argc, char **argv){
   if(getenv("BOMBMANIA_DATA_PATH"))
      Settings::s_sDataDir = getenv("BOMBMANIA_DATA_PATH");
   else
      Settings::s_sDataDir = DATA_PATH;

   // Launch
   try{

      // Configure
      Settings::getInstance();
      init(argc, argv);

      showMenu();
   }
   catch(const char * error){
      printf("%s", error);
   }

   return 0;
}
