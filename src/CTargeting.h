#ifndef _CTARGETING_H_
    #define _CTARGETING_H_

#include "CSurface.h"
#include "GFXMODE.h"
#include "Define.h"
#include "CCamera.h"
#include "CEntity.h"
#include "CEnemy.h"

class CTargeting {
	public:

		SDL_Surface*    Surf_Target;  //the surface for the actual target..
		SDL_Surface*    Surf_Poss_Target;

		bool Targeting_Mode;
			
		CEnemy *Target;		//pointer to the actual target...
	
	public:

		CTargeting();

		bool OnLoad(char* File, char* File2);
		void OnRender(SDL_Surface* Surf_Display);
		void OnCleanup();

};

#endif