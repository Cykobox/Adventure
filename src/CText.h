#ifndef _CText_H_
        #define _CText_H_
        
#include <SDL.h>
#include <SDL_image.h>  
#include <SDL_ttf.h>      
#include "GFXMODE.h"
#include "CSurface.h"
#include "CRenderable.h"
#include <string>

class CText : public CRenderable{
      public:
           SDL_Color    T_Color;
           
           TTF_Font*    Font;
           char Text[128];

		   int X;
           int Y;
      public:
           CText();
           void OnLoad(char* File, int Size);        //file for the font type, and size of the font
           void OnRender(SDL_Renderer *pRenderer);
           void OnCleanup();
      
      
};        

#endif
