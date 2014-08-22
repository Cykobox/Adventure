#include "ADV.h"
#include "CMenu.h"
#include "CMessage.h"


void AdvGame::OnRender() {

switch (GFXMODE::GFXMODE_Control.GET_GFX_MODE()) {
     case (GFX_MODE_PC): {
          
          //SDL_FillRect(Surf_Display, NULL, 0x00000);        
          //Fills Surf_Display with black, before drawing
          //everything else... kinda of inefficient but it works 
          //when I don't have a background.     --CRASHES--... don't know why... but dont need it so...
		  
		  SDL_RenderClear(mpRenderer);  //Clears SDL 2.0 Render
		  
		  
		  /*---------------------------------------------------------------------------------------------------- 
		  THIS IS ALLLLLLLLL THE STUFF THAT CALLS PREVIOUS VERSIONS OF ON RENDER FUNCTIONS WHICH USE SURFACES... 
		  THESE ALL NEED TO BE REPLACES BY NEW ONRENDER CALLS THAT USE TEXTURES... AS THESE ARE FIXED THEY WILL BE REINSTATED
		  ------------------------------------------------------------------------------------------------------
          CArea::AreaControl.OnRender(Surf_Display, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());
          
          for(int i = 0; i < CEntity::EntityList.size(); i++) {
              if(!CEntity::EntityList[i]) continue;
			  if (CEntity::EntityList[i]->Dead == false) {CEntity::EntityList[i]->OnRender(Surf_Display);}
          }
          
          ActionControl.Messages.OnRender(Surf_Display);                   //Render the Messages on Surface

          if (Menu_Vis) {                                    //If the Menu is open, render the menu on screen too.
               Menu.OnRender(&Player1, Surf_Display, 640, 0);
          }

          //SDL_Flip(Surf_Display);                            //Put that shits on da screen bitchez!!
          -------------------------------------------------------------------------------------------------------------
		  */
		  
		  
		  SDL_RenderPresent(mpRenderer);  //Put SDL 2.0 Render mpRender to screen... basically same as SDL_Flip as line above.
		  
          break;
          }
     default: {
     }
     }
}
