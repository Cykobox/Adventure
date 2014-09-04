#include "CMessage.h"
#include "CSurface.h"
#include <stdio.h>
#include <string>
#include <iostream>

CMessage::CMessage() {
    My_Texture = NULL;                 
}

bool CMessage::OnLoad(SDL_Renderer *pRenderer) {
switch (GFXMODE::GFXMODE_Control.GET_GFX_MODE()) {
     case (GFX_MODE_PC): {
          
		  LoadTexture(pRenderer, ("./images/MessageBar.bmp"));		//Loads background texture into the My_Text of Message object.
          for (int i = 0; i < 19; i++) {
              MessageArray[i].OnLoad("./fonts/PC-Font.ttf", 22);
              sprintf_s(MessageArray[i].Text, _countof(MessageArray[i].Text), " ");  //adds in one space to each message text so its not some random text or NULL
		  }
          MessageArray[0].X = 15;
          MessageArray[0].Y = 134 - 20;
          MessageArray[1].X = 15;
          MessageArray[1].Y = 134 - 38;
          MessageArray[2].X = 15;
          MessageArray[2].Y = 134 - 56;
          MessageArray[3].X = 15;
          MessageArray[3].Y = 134 - 74;
          MessageArray[4].X = 15;
          MessageArray[4].Y = 134 - 92;
          
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
			 SDL_Texture *Message_Texture = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 640, 134);
			 
			 SDL_SetRenderTarget(pRenderer, Message_Texture);		//Set our renderer to render all things to our Menu_Text texture and not to screen... so keep the menu on one texture
			 SDL_RenderClear(pRenderer);							// Clears anything on Texture;
			 
			 SDL_RenderCopy(pRenderer, My_Texture, NULL, NULL);		//copies Menu ackground image to Message_Texture first.
			 for (int i = 0; i < 20; i++) {                      //This version, for PC graphics, draws the messages to the Message_Texture of this function,
                  MessageArray[i].OnRender(pRenderer);           //and then draws the Message_Texture to the screen... it is set up however
             }													 //For later versions, demonstrated below, to draw messages, anywhere on the screen
			 
			 SDL_SetRenderTarget(pRenderer, NULL);				 // Set the place to render back to NULL, meaning "The Screen"
			 
			 SDL_Rect DESRect;
			 DESRect.h = 134;
			 DESRect.w = 640;
			 DESRect.x = 0;
			 DESRect.y = 346;
			 int *MessTextW = NULL;
			 int *MessTextH = NULL;
			 SDL_QueryTexture(Message_Texture, NULL, NULL, MessTextW, MessTextH); //Set the width and heights of the current texture.
			 SDL_RenderCopy(pRenderer, Message_Texture, NULL, &DESRect);      //Renders our Message_Texture, with all our messages and background... to the screen.													 //with their own X and Y coordinates, directly to the Screen...	
			 std::cout << "MessTextw = " << MessTextW << "; MessTextH = " << MessTextH << "\n";
			 SDL_DestroyTexture(Message_Texture);
			 
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
		  std::cout << "MessageArray[0].text = " << MessageArray[0].Text << "\n";
		  sprintf_s(MessageArray[0].Text, _countof(MessageArray[0].Text), Message);
		  std::cout << "MessageArray[0].text = " << MessageArray[0].Text << "\n";
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
