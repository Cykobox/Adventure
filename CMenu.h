#ifndef _CMENU_H_
        #define _CMENU_H_
        
#include "CText.h"
#include <SDL.h>
#include <SDL_image.h>        
#include "CPlayer.h"

class CMenu {
      public:             
             SDL_Surface*      Surf_Menu;
             
             CText              Name;
			 CText			    T_HP_LABEL;
			 CText			    T_MP_LABEL;
			 CText			    T_AP_LABEL;
			 CText			    T_TARGETING_MODE;
			 CText			    T_Tar_X;
			 CText				T_Tar_Y;
			 CText				T_PAUSE;
			 CText				T_Facing;
      public:
             CMenu();
             bool OnLoad();
             void OnRender(CPlayer* Player1, SDL_Surface* Surf_Display, int X, int Y);
             void OnCleanup();
             
};

#endif
