#include "pthread.h"
#include "gui/cegui.h"
#include "opengl/opengl.h"
#include "opengl/playerOpengl.h"
#include "opengl/gameOpengl.h"
#include "opengl/worldOpengl.h"
#include "objectLoader/loader.h"

GLfloat light1_ambient[]= { 0.1f, 0.1f, 0.1f, 0.1f };
GLfloat light1_diffuse[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light1_specular[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light1_position[]= { 100.0f, 0.0f, 20000.0f, 1.0f };

GLfloat mat_metal1_ambient[]= { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat mat_metal1_diffuse[]= { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat mat_metal1_specular[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat mat_metal1_shininess[]= { 1.0f };

//Instances of globaly declared variables.
WorldOpengl * world; //World instance. May be this class could be static, but it doesnt metter.
GameOpengl * game;

pthread_t drawThread;

void exitFunction(){
}

void init(int argc, char **argv){
    atexit(exitFunction);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH);

    glutCreateWindow(WINDOW_TITLE);
    glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, windowWidth, windowHeight);

    //glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);

    setCamera();
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_TEXTURE_2D);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_ALPHA_TEST);
    //glEnable(GL_BLEND);
    // glAlphaFunc(GL_GREATER, 0.1f);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    world = new WorldOpengl();

    getCurTime(world->timeStart);
    
    ObjectLoader::LoadObject("asteroid_unbreakable");

};
void end(){};		//UnInitialize output
void showWelcome(){};	//will be deleted

//The beginning of game, basic input handling
void startGame(){

   pthread_create(&drawThread, NULL, drawThreadProc, NULL);

   menu->showMenu(CEGui::wMainMenu, false);
}

//Show main menu
void showMenu(){
   
   menu = new CEGui();
   glutReshapeFunc(onResize);
   menu->showLoadingScreen();
   
   glutMainLoop();   
}
//void draw(WorldPiece* piece);	//Function to draw given world piece
//void cleanScreen(){};
void drawScreen(){};
int getInput(){return 0;};
void gameOver(){};
void gameRestart(){};
void updateStats(){};



