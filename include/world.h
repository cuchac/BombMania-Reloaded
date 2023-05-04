#ifndef WORLD_H_
#define WORLD_H_

//Definition of pieces of world. 
#define SPACE        0
#define WALL_UNBRK   3
#define WALL_BRK     2
#define BOMB         5
#define PLAYER       4
#define FIRE         1

#define HORIZONTAL   1
#define VERTICAL     2

#define STATE_INITIALIZED 1
#define STATE_DESTROYED   2

//The parent of every piece in the world
class WorldPiece{
	public:
                        WorldPiece(int x_, int y_){x=x_;y=y_;state=STATE_INITIALIZED;};
      virtual          ~WorldPiece();

      virtual void      Draw()=0;
      virtual bool      Burn();
      void              Destroy();
      
   public:
      int      x,y;
      float    rotx, roty, rotz;
		bool     destroyable;
		int      type;
      int      state;
};

//The derivates of WorldPiece class

class WallBrk:public WorldPiece{
	public:
                        WallBrk(int x, int y);
      
      virtual bool      Burn();
      void              Draw();

   public:
      float    actionTime;
};

class WallUnBrk:public WorldPiece{
	public:
                        WallUnBrk(int x, int y);
      void              Draw();
};

class Space:public WorldPiece{
	public:
                        Space(int x, int y);
		void              Draw();
};

class Fire:public WorldPiece{
	public:
                        Fire(int x, int y, int direction);
      //virtual        ~Fire();
      
      void              Draw();

   public:
		int      direction;
};

class Bomb:public WorldPiece{
	public:
                        Bomb(int x, int y, int fireLen);
      //virtual        ~Bomb();
      
		void              Boom();
		void              Clean();
		static void       timeBoom(void *);
		static void       timeClean(void *);
		void              Draw();
      
   public:
      int      fireLen;
		int      boomed;
};

//Class representing the level=world. Keeps the data
class World{
	public:
                        World();
      virtual          ~World(){};
      
		virtual void      loadWorld(const char * fileName);
      virtual void      unloadWorld();
		void              reload();
		void              redraw();

   public:
      int      worldWidth, worldHeight;
      WorldPiece ***worldData;
      char     levelName[256];
};


#endif /*WORLD_H_*/
