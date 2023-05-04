#include "world.h"
#include <cstring>
#include "bombmania.h"
#include "support.h"
#include "xml/xml.h"

#include <opengl/worldOpengl.h>
#include <opengl/gameOpengl.h>

WallBrk::WallBrk(int x, int y):WorldPiece(x,y){
	destroyable = true;
	type=WALL_BRK;
        actionTime=0;
}

WallUnBrk::WallUnBrk(int x, int y):WorldPiece(x,y){
	destroyable = false;
	type=WALL_UNBRK;
}

Space::Space(int x, int y):WorldPiece(x,y){
	destroyable=true;
	type=SPACE;
}

Fire::Fire(int x, int y, int direction_):WorldPiece(x,y){
	destroyable=true;
	type=FIRE;
	direction=direction_;
}

//#include <time.h>
//#include <unistd.h>

Bomb::Bomb(int x, int y, int fireLen_):WorldPiece(x,y){
	destroyable = true;
	type=BOMB;	
	boomed=false;
        fireLen = fireLen_;
	
	//setTimer(2,(void *)Bomb::timeBoom,(void*)this);
		
}

bool WorldPiece::Burn(){
  //state = STATE_DESTROYED;
  world->worldData[x][y]=new Fire(x,y,0);
  delete this;
  return true;
}


bool WallBrk::Burn(){
  state = STATE_DESTROYED;
  
  return true;
}

void WorldPiece::Destroy(){
	world->worldData[x][y]=new Space(x,y);
        delete this;
}

void Bomb::timeBoom(void * object){
	((Bomb*)object)->Boom();
}

void Bomb::timeClean(void * object){
	((Bomb*)object)->Clean();
	world->worldData[((Bomb*)object)->x][((Bomb*)object)->y]=new Space(((Bomb*)object)->x,((Bomb*)object)->y);
	//DELETE(((WorldPiece*)object);
	((WorldPiece*)object)->Destroy();
}


void Bomb::Boom(){	
	int tmpx, tmpy, direction, limit;
	for(int i=0;i<4;i++){
                limit = 0;
		direction = ((directions[i][0]==0)?VERTICAL:HORIZONTAL);
		tmpx=x;tmpy=y;
                while(world->worldData[tmpx+=directions[i][0]][tmpy+=directions[i][1]]->type<=FIRE && ++limit<fireLen){
			if(world->worldData[tmpx][tmpy]->type==FIRE){
				((Fire*)world->worldData[tmpx][tmpy])->direction|=direction;
				continue;
			}
			else{
				delete world->worldData[tmpx][tmpy];
				world->worldData[tmpx][tmpy]=new Fire(tmpx,tmpy,direction);
			}
		}
		if(world->worldData[tmpx][tmpy]->destroyable){
			if(world->worldData[tmpx][tmpy]->type==BOMB)continue;
			else {
				world->worldData[tmpx][tmpy]->Burn();
                          /*delete world->worldData[tmpx][tmpy];//world->worldData[tmpx][tmpy]->burn();
                          world->worldData[tmpx][tmpy]=new Fire(tmpx,tmpy,direction);*/
			}
		}
	}
	
	boomed=true;
	game->CheckAlive();
	
	//setTimer(1,(void *)Bomb::timeClean,this);
	//sleep(1);
	//timeClean(this);
}

void Bomb::Clean(){	
	int tmpx, tmpy, direction;
	for(int i=0;i<4;i++){
		direction = ((directions[i][0]==0)?VERTICAL:HORIZONTAL);
		tmpx=x;tmpy=y;
		while(world->worldData[tmpx+=directions[i][0]][tmpy+=directions[i][1]]->type == FIRE){
			//refresh();
			//if(((Fire*)world->worldData[tmpx][tmpy])->direction == 0)mvprintw(10,22,"Pomooc!!!!!!!!!!!!!11",tmpx, tmpy);
			//refresh();
			((Fire*)world->worldData[tmpx][tmpy])->direction &= ~direction;
			if(((Fire*)world->worldData[tmpx][tmpy])->direction)continue;
			//refresh();
			delete world->worldData[tmpx][tmpy];
			world->worldData[tmpx][tmpy]=0;
			WorldPiece * temp= new Space(tmpx,tmpy);
			world->worldData[tmpx][tmpy]= temp;
			//refresh();
		}
	}
}

/*Bomb::~Bomb(){	
	//world->worldData[x][y]=new Space(x,y);
	//DELETE(this;
}

Fire::~Fire(){
	//world->worldData[x][y]=new Space(x,y);
	//DELETE(this;
}*/

WorldPiece::~WorldPiece(){	
	//world->worldData[x][y]=new Space(x,y);
	//DELETE(this;
}

void World::loadWorld(const char * level){
	
	Xml xmlFile;

   if(!xmlFile.load(CREATE_PATH(LEVELS_PATH), level))
      return;
   
	TiXmlElement* xmlRoot = xmlFile.getRoot();
	
	worldWidth = atoi(xmlRoot->Attribute("width"));
	worldHeight = atoi(xmlRoot->Attribute("height"));
	
   TiXmlElement* pCell = xmlRoot->FirstChildElement("cells")->FirstChildElement();
	int cellCount = 0;

   for( ; pCell; pCell = pCell->NextSiblingElement())
      cellCount++;

   if(cellCount != worldWidth*worldHeight)
   {
      printf("Error loading level: Cells count does not match!\n");
      return;
   }
	
	printf("Succesfully loaded! width=%d, height=%d\n", worldWidth, worldHeight);

   worldData=new WorldPiece**[worldHeight];

   for(int x=0;x<worldHeight;x++)
      worldData[x]=new WorldPiece*[worldWidth];

   pCell = xmlRoot->FirstChildElement("cells")->FirstChildElement();

   for(int y=0;y<worldHeight;y++)
      for(int x=0;x<worldWidth;x++)
      {
         int type = atoi(pCell->Attribute("type"));
         switch(type)
         {
            case 1:
               worldData[x][y]=new WallUnBrk(x,y);
               break;
               
            case 2:
               worldData[x][y]=new WallBrk(x,y);
               break;
               
            default:
               worldData[x][y]=new Space(x,y);
         }
         pCell = pCell->NextSiblingElement();
      }

   strncpy(levelName, level, ARRAYSIZE(levelName));
   
   return;
}

void World::unloadWorld(){

   for(int x=0;x<worldWidth;x++)
      for(int y=0;y<worldHeight;y++)
         delete worldData[x][y];
   
   for(int x=0;x<worldHeight;x++)
      delete [] worldData[x];

   if(worldData)
      delete [] worldData;

   worldHeight = 0;
   worldWidth = 0;

}

void World::reload(){
   unloadWorld();
   loadWorld(levelName);
}

//Call the output moduls draw() function to redwaw every piece of world
void World::redraw(){
   int x;
	for(x=0;x<world->worldWidth;x++)
		for(int y=0;y<world->worldHeight;y++)
			world->worldData[x][y]->Draw();
      
	for(x=0;x<game->playersCount;x++)		
		game->players[x]->Draw();
   
	drawScreen();
}

void cleanScreen(){
	//erase();
	//refresh();
}

World::World(){
}
