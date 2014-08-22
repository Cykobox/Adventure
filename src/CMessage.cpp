#include "CMessage.h"
#include "CSurface.h"
#include <stdio.h>
#include <string>

CMessage::CMessage() {
    Surf_Message = NULL;                 
}

bool CMessage::OnLoad() {
switch (GFXMODE::GFXMODE_Control.GET_GFX_MODE()) {
     case (GFX_MODE_PC): {
          //SDL_FillRect(Surf_Message, NULL, 0x00000); //I Still don't know why this doesn't work, but it kills it so...
          Surf_Message = CSurface::OnLoad("./images/MessageBar.bmp");
          
          for (int i = 0; i < 19; i++) {
              MessageArray[i].OnLoad("./fonts/PC-Font.ttf", 22);
              sprintf_s(MessageArray[i].Text, _countof(MessageArray[i].Text), " ");
          }
          MessageArray[0].X = 15;
          MessageArray[0].Y = WHEIGHT - 20;
          MessageArray[1].X = 15;
          MessageArray[1].Y = WHEIGHT - 38;
          MessageArray[2].X = 15;
          MessageArray[2].Y = WHEIGHT - 56;
          MessageArray[3].X = 15;
          MessageArray[3].Y = WHEIGHT - 74;
          MessageArray[4].X = 15;
          MessageArray[4].Y = WHEIGHT - 92;
          break;
     }
     default: {
     }
};
return true;
}

void CMessage::OnRender(SDL_Surface* Surf_Display) {
     switch (GFXMODE::GFXMODE_Control.GET_GFX_MODE()) {
         case (GFX_MODE_PC): {
             CSurface::OnDraw(Surf_Display, Surf_Message, 0, 500); //draws the black first                      
             for (int i = 0; i < 20; i++) {                      //This version, for PC graphics, draws the messages to a specific console area,
                  MessageArray[i].OnRender(Surf_Display);        //and then draws the console area to the main surf_Display... it is set up however
             }                                                   //For later versions, demonstrated below, to draw messages, anywhere on the screen
             break;                                              //with their own X and Y coordinates, directly to the main surf_Display...
         }                                                        
         case (GFX_MODE_8BIT): {
              for (int i = 0; i < 20; i++) {
                  MessageArray[i].OnRender(Surf_Display);
              }
              break;
         }
         default: {
         }
     };
}

void CMessage::AddMessage(char* Message, int X, int Y, int Length) {
	 switch (GFXMODE::GFXMODE_Control.GET_GFX_MODE()) {
     case (GFX_MODE_PC): {
          for (int i = 4; i > -1; i--) {
			  sprintf_s(MessageArray[i].Text, _countof(MessageArray[i].Text), MessageArray[i - 1].Text);
          }
		  sprintf_s(MessageArray[0].Text, _countof(MessageArray[0].Text), Message);
          
		  break;
     }
     default: {
     }
     };
}

void CMessage::OnCleanup() {
     SDL_FreeSurface(Surf_Message);
     for (int i = 0; i < 20; i++) {
         MessageArray[i].OnCleanup();
     }
}
