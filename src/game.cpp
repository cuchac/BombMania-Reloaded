#include "game.h"
#include "bombmania.h"
#include "module.h"

#include <opengl/worldOpengl.h>
#include <opengl/gameOpengl.h>

Game::Game(){
	gameState = STATE_STOPPED;
	playersCount = 0;
}

//Handle player adding. This is because Im sclerotic and i would forgot to increment playerCount :))
void Game::AddPlayer(char * name, Controls *controls, int skin){
	players[playersCount]=new Player(name,controls, skin, playersCount);
	playersCount++;
}

void Game::startRound(){
		
	game->gameState=STATE_RUNNING;
	for(int x=0;x<game->playersCount;x++){
		players[x]->placePlayer(-1,-1);
		players[x]->playerState = PLAYER_ALIVE;
	}
	//cleanScreen();
	world->redraw();
	
	int ch;
	while((ch = getInput()) && gameState==STATE_RUNNING){
		switch(ch){
			case 'q':
				gameState=STATE_QUIT;
				return;
			default:
				for(int x=0;x<playersCount;x++)
					if(players[x]->handleKey(ch))break;
				world->redraw();
		}
	}
	if(gameState==STATE_QUIT)restart();
	if(gameState==STATE_STOPPED)gameOver();
	
}

void Game::startGame(){
	game->gameState=STATE_RUNNING;
	
	while(game->gameState!=STATE_QUIT)
		startRound();
}


//Check, whether player is allready dead :))) This means, wheter he stands on fire or boomed bomb.
void Game::CheckAlive(){
	for(int i=0;i<game->playersCount;i++){
           if(players[i]->x > 0 && players[i]->x > 0 &&
             world->worldData[players[i]->x][players[i]->y] != 0 &&
             (world->worldData[players[i]->x][players[i]->y]->type==FIRE || 
             (world->worldData[players[i]->x][players[i]->y]->type==BOMB && 
             ((Bomb*)world->worldData[players[i]->x][players[i]->y])->boomed))){
		game->players[i]->Die();
		}
	}
}

void Game::restart(){
	world->reload();
	for(int x=0;x<game->playersCount;x++){
		game->players[x]->lives=LIVES;
		game->players[x]->placePlayer(-1,-1);
	}
	
	gameRestart();
}
