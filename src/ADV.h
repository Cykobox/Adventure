#ifndef _ADV_H
        #define _ADV_H_             

#include "GFXMODE.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "CEvent.h"
#include "CArea.h"
#include "CMenu.h"
#include "CInventory.h"
#include "CEnemy.h"
#include "CActionListControl.h"

class AdvGame : public CEvent {
      private:
		  bool Running;
              
          SDL_Surface* Surf_Display;

		  SDL_Window* mpMainWindow;
		  SDL_Renderer *mpRenderer;

          
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
		  void OnKeyDown(SDL_Scancode Scan_Code);
		  void OnKeyUp(SDL_Scancode Scan_Code);
          void Reset();
		  void EmptyEnemyList();			// Empties the list of active enemies, despawning any that are active.

private:
	void OnKeyDownPC(SDL_Scancode Scan_Code);
	void OnKeyDown8Bit(SDL_Scancode Scan_Code);

};

// the game object.
extern AdvGame Game;

#endif
