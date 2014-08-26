#ifndef _CMENU_H_
        #define _CMENU_H_
        
#include "CText.h"
#include <SDL.h>
#include <SDL_image.h>        
#include "CPlayer.h"
#include "CRenderable.h"

class CMenu : public CRenderable {
      public:             
             
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
	 
				 int Menu_Width;
				 int Menu_Height;
				 int Menu_X;
				 int Menu_Y;
      public:
             CMenu();
             bool OnLoad(SDL_Renderer *pRenderer, int height, int width, int x, int y);
             void OnRender(CPlayer* Player1, SDL_Renderer* pRenderer);
             void OnCleanup();
             
};

#endif
