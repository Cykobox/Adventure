#ifndef _CMESSAGE_H_
        #define _CMESSAGE_H_
        
#include "CText.h"
#include <SDL.h>
#include <SDL_image.h> 
#include "GFXMODE.h"
#include "Define.h"

class CMessage{
      public:
             CMessage();
             SDL_Surface* Surf_Message;
             
             CText MessageArray[20];
             
             
      public:
             bool OnLoad();
             void OnRender(SDL_Surface* Surf_Display);
             void OnCleanup();
             void AddMessage(char* Message, int X, int Y, int Length);             
};


#endif
