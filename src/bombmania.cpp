#include <stdio.h>
#include <iostream>

#include "bombmania.h"
#include "module.h"
#include "support.h"
#include "settings.h"
#include <stdlib.h>
#include <libgen.h>

int main(int argc, char **argv){
   
   // Get base dir of executable
   char * sFullPath = realpath(argv[0], NULL);
   
   Settings::s_sExeDir = dirname(sFullPath);
   if(getenv("BOMBMANIA_DATA_PATH"))
      Settings::s_sExeDir += getenv("BOMBMANIA_DATA_PATH");
   else
      Settings::s_sExeDir += "/" BOMBMANIA_DATA_PATH;
   
   if(sFullPath)
      free(sFullPath);

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
