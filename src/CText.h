#ifndef _CText_H_
        #define _CText_H_
        
#include <SDL.h>
#include <SDL_image.h>  
#include <SDL_ttf.h>      
#include "GFXMODE.h"
#include "CSurface.h"
#include <string>

class CText {
      public:
           SDL_Surface* Surf_Print;
           SDL_Color    T_Color;
           
           TTF_Font*    Font;
           char Text[128];

		   int X;
           int Y;
      public:
           CText();
           void OnLoad(char* File, int Size);        //file for the font type, and size of the font
           void OnRender(SDL_Surface* Surf_Display);
           void OnCleanup();
      
      
};        

#endif
