//#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "GL/glut.h"
#include "objectLoader/object.h"
#include "objectLoader/3dsloader.h"
#include "objectLoader/texture.h"

#define WINDOW_TITLE    "BomB Mania"
#define WINDOW_WIDTH    640
#define WINDOW_HEIGHT   480

#define FOVY 40
#define MIN_DIST 1
#define MAX_DIST 40000

double scale=10;
int    xnew=0, xold=0, ynew=0, yold=0, znew=0, zold=0, stav=0;
int    x2=0, y2=0, z2=0;

GLfloat light1_ambient[]= { 0.1f, 0.1f, 0.1f, 0.1f };
GLfloat light1_diffuse[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light1_specular[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light1_position[]= { 100.0f, 0.0f, -10.0f, 1.0f };

GLfloat mat_metal1_ambient[]= { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat mat_metal1_diffuse[]= { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat mat_metal1_specular[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat mat_metal1_shininess[]= { 1.0f };

obj_type ship01;
obj_type ship02;
obj_type mine;

void drawObject(obj_type *object)
{
    int l_index;
    glMaterialfv (GL_FRONT, GL_AMBIENT, mat_metal1_ambient);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_metal1_diffuse);
    glMaterialfv (GL_FRONT, GL_SPECULAR, mat_metal1_specular);
    glMaterialfv (GL_FRONT, GL_SHININESS, mat_metal1_shininess);
    glBindTexture(GL_TEXTURE_2D, object->id_texture);
    glBegin(GL_TRIANGLES);
    for(l_index=0; l_index<object->polygons_qty; l_index++)
    {
        glNormal3f(object->normal[object->polygon[l_index].a].x, object->normal[object->polygon[l_index].a].y, object->normal[object->polygon[l_index].a].z);
        glTexCoord2f(object->mapcoord[object->polygon[l_index].a].u, object->mapcoord[object->polygon[l_index].a].v);
        glVertex3f(object->vertex[object->polygon[l_index].a].x, object->vertex[object->polygon[l_index].a].y, object->vertex[object->polygon[l_index].a].z);
        glNormal3f(object->normal[object->polygon[l_index].b].x, object->normal[object->polygon[l_index].b].y, object->normal[object->polygon[l_index].b].z);
        glTexCoord2f(object->mapcoord[object->polygon[l_index].b].u, object->mapcoord[object->polygon[l_index].b].v);
        glVertex3f(object->vertex[object->polygon[l_index].b].x, object->vertex[object->polygon[l_index].b].y, object->vertex[object->polygon[l_index].b].z);
        glNormal3f(object->normal[object->polygon[l_index].c].x, object->normal[object->polygon[l_index].c].y, object->normal[object->polygon[l_index].c].z);
        glTexCoord2f(object->mapcoord[object->polygon[l_index].c].u, object->mapcoord[object->polygon[l_index].c].v);
        glVertex3f(object->vertex[object->polygon[l_index].c].x, object->vertex[object->polygon[l_index].c].y, object->vertex[object->polygon[l_index].c].z);
    }
    glEnd();
}

void onInit(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOVY, (GLfloat)WINDOW_WIDTH/(GLfloat)WINDOW_HEIGHT, MIN_DIST, MAX_DIST);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_TEXTURE_2D);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    ObjLoad(&ship01, "data/fighter01.3ds", "data/fighter01.bmp");
    ObjLoad(&ship02, "data/fighter02.3ds", "data/fighter02.bmp");
    ObjLoad(&mine, "data/mine.3ds", "data/mine.bmp");
}

void onResize (int width, int height)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOVY, (GLfloat)width/(GLfloat)height, MIN_DIST, MAX_DIST);
    glutPostRedisplay();
}

void onDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    //glPushMatrix();
    int x = xnew;
    int y = ynew;
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -480.0);
        glTranslatef(0.0f, 0.0f, -znew);
        //glRotatef(ynew, 0.0f, 1.0f, 0.0f);
        //glRotatef(-xnew, 0.0f, 0.0f, 1.0f);
        glTranslatef(120.0f, 0.0f, 0.0f);
        glRotatef(y, 1.0f, 0.0f, 0.0f);
        glRotatef(x, 0.0f, 0.0f, 1.0f);
        drawObject(&ship02);
        glRotatef(-x, 0.0f, 0.0f, 1.0f);
        glRotatef(-y, 1.0f, 0.0f, 0.0f);
        glTranslatef(-240.0f, 0.0f, 0.0f);
        glRotatef(y, 1.0f, 0.0f, 0.0f);
        glRotatef(x, 0.0f, 0.0f, 1.0f);
        drawObject(&ship01);
        glRotatef(-x, 0.0f, 0.0f, 1.0f);
        glRotatef(-y, 1.0f, 0.0f, 0.0f);
        glTranslatef(120.0f, 0.0f, 0.0f);
        glRotatef(y, 1.0f, 0.0f, 0.0f);
        glRotatef(x, 0.0f, 0.0f, 1.0f);
        drawObject(&mine);
    //glPopMatrix();
    //glMatrixMode(GL_PROJECTION);
    //glPushMatrix();
        //glLoadIdentity();
        //glOrtho(0, 512, 0, 384, -1, 1);
        //glRasterPos2i(0, 0);
        //drawInfo(a, b, c, dt, maxiter, scale, xnew, ynew);
    //glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void onMouse(int button, int state, int x, int y)
{
    if (button==GLUT_LEFT_BUTTON) {
        if (state==GLUT_DOWN) {
            stav=1;
            x2=x;
            y2=y;
        }
        else {
            stav=0;
            xold=xnew;
            yold=ynew;
        }
    }
    if (button==GLUT_RIGHT_BUTTON) {
        if (state==GLUT_DOWN) {
            stav=2;
            z2=y;
        }
        else {
            stav=0;
            zold=znew;
        }
    }
    glutPostRedisplay();
}

void onMotion(int x, int y)
{
    if (stav==1) {
        xnew=xold+x-x2;
        ynew=yold+y-y2;
        glutPostRedisplay();
    }
    if (stav==2) {
        znew=zold+y-z2;
        glutPostRedisplay();
    }
}

#ifdef __WIN32
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    glutInit(&__argc, __argv);
#else
int main(int argc, char **argv)
{
#endif

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(WINDOW_TITLE);
    glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutDisplayFunc(onDisplay);
    glutReshapeFunc(onResize);
    //glutKeyboardFunc(onKeyboard);
    //glutSpecialFunc(onSpecial);
    glutMouseFunc(onMouse);
    glutMotionFunc(onMotion);
    onInit();
    glutMainLoop();
    return 0;
}
