#ifndef _CMESSAGE_H_
        #define _CMESSAGE_H_
        
#include "CText.h"
#include <SDL.h>
#include <SDL_image.h> 
#include "GFXMODE.h"
#include "Define.h"
#include "CRenderable.h"

class CMessage : public CRenderable {
      public:
             CMessage();
             
             CText MessageArray[20];
             
             
      public:
             bool OnLoad(SDL_Renderer *pRenderer);
             void OnRender(SDL_Renderer *pRenderer);
             void OnCleanup();
             void AddMessage(char* Message, int X, int Y, int Length);             
};


#endif
