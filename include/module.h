#ifndef MODULE_H_
#define MODULE_H_

//Main interface of output/input module

#include "world.h"
void init(int argc, char **argv);	//initialize output
void end();		//UnInitialize output
void showWelcome();	//will be deleted
void showMenu();	//Show main menu
//void startGame();	//The beginning of game, basic input handling
//void draw(WorldPiece* piece);	//Function to draw given world piece
void cleanScreen();
void drawScreen();
int getInput();
void gameOver();
void gameRestart();
void updateStats();

#endif /*MODULE_H_*/
