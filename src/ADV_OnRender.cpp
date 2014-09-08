#include "ADV.h"
#include "CMenu.h"
#include "CMessage.h"


void AdvGame::OnRender()
{

	switch (GFXMODE::GFXMODE_Control.GET_GFX_MODE())
	{
		case (GFX_MODE_PC):
		{ 
			SDL_RenderClear(mpRenderer);  //Clears SDL 2.0 Render
		  
			for (int i = 0; i < CEntity::EntityList.size(); i++)
			{
				if (!CEntity::EntityList[i]) continue;
				if (CEntity::EntityList[i]->Dead == false) { CEntity::EntityList[i]->OnRender(mpRenderer); }
			}

			/*---------------------------------------------------------------------------------------------------- 
			THIS IS ALLLLLLLLL THE STUFF THAT CALLS PREVIOUS VERSIONS OF ON RENDER FUNCTIONS WHICH USE SURFACES... 
			THESE ALL NEED TO BE REPLACES BY NEW ONRENDER CALLS THAT USE TEXTURES... AS THESE ARE FIXED THEY WILL BE REINSTATED
			------------------------------------------------------------------------------------------------------
			CArea::AreaControl.OnRender(Surf_Display, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());
			-------------------------------------------------------------------------------------------------------------
			*/

			//If the Menu is open, render the menu on screen too.
			if (Menu_Vis)
			{
				Menu.OnRender(&Player1, mpRenderer);
			}

			//Render the Messages on Screen
			//ActionControl.Messages.OnRender(mpRenderer);
			ActionControl.OnRenderMessage(mpRenderer);
			SDL_RenderPresent(mpRenderer);  //Put SDL 2.0 Render mpRender to screen... basically same as SDL_Flip as line above.
		  
			break;
		}
		default:
			break;
     }
}
