#include "CText.h"
#include <iostream>


CText::CText(){
     Font = NULL;
     My_Texture = NULL;
}

void CText::OnLoad(char* File, int Size) {            
     Font = TTF_OpenFont(File, Size);
}

void CText::OnRender(SDL_Renderer *pRenderer) {
     SDL_Color textColor = { 255, 255, 255 };
	 SDL_Surface *Surf_Print = NULL;
	 if (Font != NULL) {
          Surf_Print = TTF_RenderText_Solid(Font, Text, textColor);
     }
	 My_Texture = SDL_CreateTextureFromSurface(pRenderer, Surf_Print);
	 
	 SDL_Rect DesRect;

	 DesRect.x = X;
	 DesRect.y = Y;
	 
	 SDL_QueryTexture(My_Texture, NULL, NULL, &DesRect.w , &DesRect.h); //Set the width and heights of the current texture.
	 
	 std::cout << "Message = " << Text << "\n" << "X = " << DesRect.x << "; Y = " << DesRect.y << "; W = " << DesRect.w << "; H = " << DesRect.h << "\n";
	 //debug tool
	 
	 SDL_RenderCopy(pRenderer, My_Texture, NULL, &DesRect);
	 SDL_FreeSurface(Surf_Print); 
}

void CText::OnCleanup() {
     DestroyTextures();
     if(Font != NULL) TTF_CloseFont(Font);
}
