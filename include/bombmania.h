#ifndef GLOBALS_H_
#define GLOBALS_H_

// Include config
#ifdef _HAVE_CONFIG
#include "config.h"
#endif

//Define the constants .... may be implemented furtermore in settings
#define LIVES 2 //Number of players lives on game start

#ifndef DATA_PATH
#warning "Using fallback data path!"
#define DATA_PATH "./res/"
#endif

#define CREATE_PATH(a) (Settings::s_sDataDir + (a)).c_str()

#define MODELS_PATH "models/"
#define OBJECTS_PATH "objects/"
#define TEXTURES_PATH "bitmaps/"
#define LEVELS_PATH "levels/"
#define GUI_PATH "gui/"

//Include necesary header files
#include "player.h"
#include "world.h"
#include "game.h"
#include "settings.h"

//#include "opengl/opengl.h"


#endif /*GLOBALS_H_*/
