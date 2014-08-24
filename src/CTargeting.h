#ifndef _CTARGETING_H_
    #define _CTARGETING_H_

#include "CSurface.h"
#include "CRenderable.h"
#include "GFXMODE.h"
#include "Define.h"
#include "CCamera.h"
#include "CEntity.h"
#include "CEnemy.h"

class CTargeting : public CRenderable{
	public:

		bool Targeting_Mode;
			
		CEnemy *Target;		//pointer to the actual target...
	
	public:

		CTargeting();

		bool OnLoad(SDL_Renderer *pRenderer, char* File, char* File2);
		void OnRender(SDL_Renderer* pRenderer);
		void OnCleanup();

};

#endif