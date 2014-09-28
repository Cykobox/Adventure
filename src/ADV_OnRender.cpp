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

			// render the map:
			CArea::AreaControl.OnRender(mpRenderer);

			// render the entities:
			for (int i = 0; i < CEntity::EntityList.size(); i++)
			{
				if (!CEntity::EntityList[i]) continue;
				if (CEntity::EntityList[i]->Dead == false) { CEntity::EntityList[i]->OnRender(mpRenderer); }
			}


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
