#ifndef _CRENDERABLE_H_
	#define _CRENDERABLE_H_

#include <SDL.h>
#include <SDL_image.h>

class CRenderable {
	public:
		CRenderable();

		SDL_Texture* My_Texture;
		
	public:	
		virtual void OnRender(SDL_Renderer* pRenderer);
		bool RenderTextureToScreen(SDL_Renderer* pRenderer, SDL_Rect SrcRect, SDL_Rect DestRect);
		bool LoadTexture(SDL_Renderer* Cur_Renderer, char* File);
		bool DestroyTextures();
};

#endif