#include "opengl/objects.h"
#include "objectLoader/texture.h"
#include "opengl/opengl.h"

int ship01,ship02;
int mine;
int asteroid01,asteroid02,asteroid03;
int explosion, explosionRed, explosionSun;
int jupiter,background;


int LoadExplosion(int* object, const char* texture){
  *object = glGenLists(100);
  

  GLUquadric *wave;
  int wave_tex;

  wave_tex = LoadTexture(texture);
  wave = gluNewQuadric();
  gluQuadricTexture(wave, GL_TRUE);
  
  glNewList(*object,GL_COMPILE);
  //glDisable(GL_LIGHTING);
  //glDisable(GL_DEPTH_TEST);
  //glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
  //glColor4f(1.0, 1.0, 1.0, ((200-(float)znew)/100));
  glBindTexture(GL_TEXTURE_2D, wave_tex);
  gluSphere(wave, 1, 50, 50);
  //glDisable(GL_BLEND);
  //glEnable(GL_DEPTH_TEST);
  //glEnable(GL_LIGHTING);
  
  glEndList();
  return 0;
}
