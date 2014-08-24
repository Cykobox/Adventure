#include "CTargeting.h"

CTargeting::CTargeting() {
	Targeting_Mode = false;
	Target = NULL;
}

bool CTargeting::OnLoad(SDL_Renderer *pRenderer, char* File, char* File2) {
	if(LoadTextureWithTransparency(pRenderer, File) == false) {
         return false;
    }
	return true;
}

void CTargeting::OnCleanup() {
	bool whocares = DestroyTextures();
}

void CTargeting::OnRender(SDL_Renderer* pRenderer) {
	if (Target != NULL) {
		switch (GFXMODE::GFXMODE_Control.GET_GFX_MODE()) {
			case GFX_MODE_PC: {
				SDL_Rect SRC_Rect;
				SDL_Rect DES_Rect;
				DES_Rect.h = DES_Rect.w = SRC_Rect.h = SRC_Rect.w = TILE_SIZE;
				SRC_Rect.x = SRC_Rect.y = 0;
				DES_Rect.x = ((Target->posX - CCamera::CameraControl.GetX()) * TILE_SIZE) - 2;
				DES_Rect.y = ((Target->posY - CCamera::CameraControl.GetY()) * TILE_SIZE) - 2;
				if (Targeting_Mode == true) { RenderTextureToScreen(pRenderer, SRC_Rect, DES_Rect); }
				//if (Targeting_Mode == false) {CSurface::OnDraw(Surf_Display, Surf_Target, ((Target->posX - CCamera::CameraControl.GetX()) * TILE_SIZE) - 2, ((Target->posY - CCamera::CameraControl.GetY()) * TILE_SIZE) - 2);}
				/* 
				   This is suppose to draw a box of a different color when the Targeting Mode is turned off... 
				   I think there is a better way of doing it than loading two different texture... Maybe color modulation or something.
				*/
				break;
			}
			case GFX_MODE_8BIT: {
				break;
			}
			default:{break;}
		}
	}
}