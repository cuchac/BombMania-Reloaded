#ifndef GAME_H_
#define GAME_H_

//Isn't 10 wariors quite enough? (for such tiny game) :)
#define MAX_PLAYERS 8

#define STATE_STOPPED	0
#define STATE_RUNNING	1
#define STATE_QUIT 		2

#include <stdlib.h>
#include "player.h"
#include "module.h"

//Game class to store all the content connected with game, like stats, players atc.  (Why class? Why Me? Why? Why? Why? God! Help!)
class Game{
	public:
		Game();
		virtual void AddPlayer(char* name, Controls* controls, int skin);//Sclerotic function
		int gameState;
        virtual void CheckAlive();
        Player *players[MAX_PLAYERS]; //Holds all the players
        int playersCount; //What the hell could this be ? :))
        virtual void startGame();
        virtual void restart();
        virtual void startRound();
        virtual ~Game(){};
};

#endif /*GAME_H_*/
