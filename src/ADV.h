#ifndef _ADV_H
        #define _ADV_H_             

#include "GFXMODE.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Define.h"
#include "CSurface.h"
#include "CAnimate.h"
#include "CEvent.h"
#include "CEntity.h"
#include "CArea.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "Define.h"
#include "CMenu.h"
#include "CInventory.h"
#include "CEnemy.h"
#include "CMessage.h"
#include "CAction.h"
#include "CActionListControl.h"
#include "CTargeting.h"
#include "SItem.h"


class AdvGame : public CEvent {
      private:
		  bool Running;
              
          SDL_Surface* Surf_Display;
              
          CEnemy Enemy;                     //This is the test Enemy;
		  CEnemy Enemy2;
		  CEnemy Enemy3;

		  


      public:
          AdvGame();
             
          int OnExecute();					//Main game loop
          bool Pause;						//True = game is paused
          bool Menu_Vis;					//Is the Menu visible or not
		  
		  CMenu Menu;
          
		  ActionListControl ActionControl;
		  
		  CInventory	InventoryManager;	// inventory manager
          
		  CPlayer Player1;                  //This is the player.
		  std::vector<CEnemy>	EnemyList;	//Enemy List.

		public:
		  bool OnInit();
          void OnEvent(SDL_Event* Event);
          void OnExit();
          void OnLoop();
          void OnRender();
          void OnCleanup();
          void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
          void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
          void Reset();
};

// the game object.
extern AdvGame Game;

#endif
