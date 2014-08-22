#include "CRenderable.h"

CRenderable::CRenderable(){
	My_Texture = NULL;
}

bool CRenderable::LoadTexture(SDL_Renderer* Cur_Renderer, char* File){
	SDL_Surface* Surf_Temp = NULL;
	if ((Surf_Temp = SDL_LoadBMP(File)) == NULL) {
		return false;
	}
	My_Texture = SDL_CreateTextureFromSurface(Cur_Renderer, Surf_Temp);
	SDL_FreeSurface(Surf_Temp);
	return true;
}

bool CRenderable::RenderTextureToScreen(SDL_Renderer* pRenderer, SDL_Rect SrcRect, SDL_Rect DestRect){
	
	if (pRenderer == NULL) {  //If renderer is NULL or not correct then cancel out and don't draw
		return false;             
	}

	SDL_RenderCopy(pRenderer, My_Texture, &SrcRect, &DestRect);   //Copy SrcRect area of My_Texture to DestRect area of pRenderer
	
	return true;  //Return and end function
}

bool CRenderable::DestroyTextures(){
	SDL_DestroyTexture(My_Texture);
	return true;
}