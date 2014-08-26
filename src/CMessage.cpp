#include "CMessage.h"
#include "CSurface.h"
#include <stdio.h>
#include <string>

CMessage::CMessage() {
    My_Texture = NULL;                 
}

bool CMessage::OnLoad() {
switch (GFXMODE::GFXMODE_Control.GET_GFX_MODE()) {
     case (GFX_MODE_PC): {
          //Surf_Message = CSurface::OnLoad("./images/MessageBar.bmp");
          
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

void CMessage::OnRender(SDL_Renderer* pRenderer) {
     switch (GFXMODE::GFXMODE_Control.GET_GFX_MODE()) {
         case (GFX_MODE_PC): {
			 LoadTexture(pRenderer, ("./images/MessageBar.bmp")); //draws the black first                      
			 SDL_SetRenderTarget(pRenderer, My_Texture);          //Set the My_Texture of the message to be the target of the renderer so all things now get endered to that texture and not the screen
			 for (int i = 0; i < 20; i++) {                      //This version, for PC graphics, draws the messages to the My_Texture of the Message object,
                  MessageArray[i].OnRender(pRenderer);           //and then draws the message object's My_Texture to the screen... it is set up however
             }													 //For later versions, demonstrated below, to draw messages, anywhere on the screen
			 SDL_SetRenderTarget(pRenderer, NULL);// Set the place to render back to NULL, meaning "The SCreen"
			 SDL_Rect DESRect;
			 DESRect.h = 134;
			 DESRect.w = 800;
			 DESRect.x = 0;
			 DESRect.y = 586;

			 SDL_RenderCopy(pRenderer, My_Texture, NULL, &DESRect);      //Renders our My_Texture, with our menu drawn on it... to the screen.													 //with their own X and Y coordinates, directly to the Screen...	
			 break;                                              
         }                                                        
         case (GFX_MODE_8BIT): {
              for (int i = 0; i < 20; i++) {
				  MessageArray[i].OnRender(pRenderer);
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
     bool whocares = DestroyTextures();
     for (int i = 0; i < 20; i++) {
         MessageArray[i].OnCleanup();
     }
}
