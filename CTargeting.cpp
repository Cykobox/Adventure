#include "CTargeting.h"

CTargeting::CTargeting() {
	Surf_Target = NULL;
	Surf_Poss_Target = NULL;
	Targeting_Mode = false;
	Target = NULL;
}

bool CTargeting::OnLoad(char* File, char* File2) {
	if((Surf_Target = CSurface::OnLoad(File)) == NULL ) {
         return false;
    }
	if((Surf_Poss_Target = CSurface::OnLoad(File2)) == NULL) {
		return false;
	}
	CSurface::Transparent(Surf_Target, 255, 0, 255);
	CSurface::Transparent(Surf_Poss_Target, 255,0, 255);
	return true;
}

void CTargeting::OnCleanup() {
	if(Surf_Target) {
         SDL_FreeSurface(Surf_Target);
    }
	if(Surf_Poss_Target) {
		SDL_FreeSurface(Surf_Poss_Target);
	}
	Surf_Target = NULL;
	Surf_Poss_Target = NULL;
}

void CTargeting::OnRender(SDL_Surface* Surf_Display) {
	if (Target != NULL) {
		switch (GFXMODE::GFXMODE_Control.GET_GFX_MODE()) {
			case GFX_MODE_PC: {
				if (Targeting_Mode == true) {CSurface::OnDraw(Surf_Display, Surf_Poss_Target, ((Target->posX - CCamera::CameraControl.GetX()) * TILE_SIZE) - 2, ((Target->posY - CCamera::CameraControl.GetY()) * TILE_SIZE) - 2);}
				if (Targeting_Mode == false) {CSurface::OnDraw(Surf_Display, Surf_Target, ((Target->posX - CCamera::CameraControl.GetX()) * TILE_SIZE) - 2, ((Target->posY - CCamera::CameraControl.GetY()) * TILE_SIZE) - 2);}
				break;
			}
			case GFX_MODE_8BIT: {
				break;
			}
			default:{break;}
		}
	}
}