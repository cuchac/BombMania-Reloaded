#ifndef DRAW_H_
#define DRAW_H_

#include <GL/glut.h>
#include <GL/glu.h>

#define WINDOW_TITLE    "BomB Mania"
#define WINDOW_WIDTH    640
#define WINDOW_HEIGHT   480

#define FOVY 40
#define MIN_DIST 2
#define MAX_DIST 256000
#define WORLD_SCALE 60

#include "pthread.h"

extern int windowWidth, windowHeight;

void setCamera();
void initOpengl(void);
void onResize (int width, int height);
void onDisplay(void);
void onIddle(void);
void drawObject(int object, float x=0, float y=0, float z=0, float rotx=0, float roty=0, float rotz=0, float scale=1);
void showFps();
void drawEnv();

void drawString(int x, int y, int z, char * string, void * font = GLUT_BITMAP_TIMES_ROMAN_24);

extern pthread_t drawThread;
void * drawThreadProc(void * parms);



#endif /*DRAW_H_*/
