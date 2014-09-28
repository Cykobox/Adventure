#ifndef _CENTITY_H_
        #define _CENTITY_H_

#include <vector>

//#include "CArea.h"
#include "CAnimate.h"
#include "CCamera.h"
#include "CFPS.h"
#include "CSurface.h"
#include "Define.h"
#include "CRenderable.h"

enum {
     ENTITY_TYPE_GENERIC = 0,  //generic, non-type, entity
     ENTITY_TYPE_PLAYER = 1,   //the player
	 ENTITY_TYPE_ENEMY = 2,    //An enemy entity
	 ENTITY_TYPE_NPC = 3,      //An NPC entity
	 ENTITY_TYPE_CHEST = 4,    //A treasure Chest
};

enum {
     ENTITY_FLAG_NONE     = 0,
     ENTITY_FLAG_GHOST    = 0x00000001,
     ENTITY_FLAG_MAPONLY  = 0x00000002,
};

class CEntity : public CRenderable{
      public:
             static std::vector<CEntity*> EntityList;
             
      protected:
                CAnimation      Anim_Control;
                
                SDL_Texture*    Entity_Texture;  // "Texture" of the entity... its picture. 
      
      public:
             int                posX;             //The Position of the Character, X coordinate, in tiles.
             int                posY;             //The Position of the Character, Y coordinate, in tiles.
             
             int                Width;         //The Width of the Character in pixels
             int                Height;        //The Height of the Character in pixels
             
             int                Type;          //Type of Entity
             bool               Dead;          //If the entity is dead
             int                Flags;         //A number of different flags             
             
             bool               Anim_Bool;     //A bool if this entity has an animation or not
             bool               Trans_Bool;    //A bool if this entity has transparency or not
      
      public:
             CEntity();                        //Constructor Function
             virtual ~CEntity();               //Destructor Function
             
      public:
             virtual bool OnLoad(SDL_Renderer *pRenderer, char* File, int Width, int Height, bool Animate, bool Transparency, int MaxFrames);
             virtual void OnLoop();
             virtual void OnRender(SDL_Renderer *pRenderer);
             virtual void OnCleanup();          //Basically clears the memory of the surface before you delete it.
             virtual void OnAnimate();
             virtual void OnCollision(CEntity* Entity);
      public:
             void OnMove(float MoveX, float MoveY);
      private:
             bool PosValid(int NewX, int NewY);
             //bool PosValidTile(MTile* Tile);
             bool PosValidEntity(CEntity* Entity, int NewX, int NewY);  
};

class CEntityCol {
      public:
             static std::vector<CEntityCol>       EntityColList;
      public:
             CEntity *EntityA;
             CEntity *EntityB;
      public:
             CEntityCol();
};


#endif
