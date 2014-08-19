#include "CText.h"


CText::CText(){
     Font = NULL;
     Surf_Print = NULL;
}

void CText::OnLoad(char* File, int Size) {            
     Font = TTF_OpenFont(File, Size);
}

void CText::OnRender(SDL_Surface* Surf_Display) {
     SDL_Color textColor = { 255, 255, 255 };

	 if (Font != NULL) {
          Surf_Print = TTF_RenderText_Solid(Font, Text, textColor);
     }
     CSurface::OnDraw(Surf_Display, Surf_Print, X, Y);
}

void CText::OnCleanup() {
     SDL_FreeSurface(Surf_Print);
     if(Font != NULL) TTF_CloseFont(Font);
}
