#include "ADV.h"

void AdvGame::OnCleanup() {
    FILE * pFile;
    pFile = fopen("./logs/log.txt", "a");
    fprintf (pFile, "OnCleanup() entered Successfully\n");
    fclose (pFile); 

	SDL_FreeSurface(Surf_Display);
	
	pFile = fopen("./logs/log.txt", "a");
    fprintf (pFile, "Reached Point 1\n");
    fclose (pFile); 
    
	for(int i = 0; i < CEntity::EntityList.size(); i++) {
            if(!CEntity::EntityList[i]) continue;
            
            CEntity::EntityList[i]->OnCleanup();
    }
	
	pFile = fopen("./logs/log.txt", "a");
    fprintf (pFile, "Reached Point 2\n");
    fclose (pFile); 
    
	CEntity::EntityList.clear();
    
	pFile = fopen("./logs/log.txt", "a");
    fprintf (pFile, "Reached Point 3\n");
    fclose (pFile); 

	CArea::AreaControl.OnCleanup();
    
	pFile = fopen("./logs/log.txt", "a");
    fprintf (pFile, "Reached Point 4\n");
    fclose (pFile);

    Menu.OnCleanup();
    
	pFile = fopen("./logs/log.txt", "a");
    fprintf (pFile, "Reached Point 5\n");
    fclose (pFile); 

	ActionControl.Messages.OnCleanup();
	
	pFile = fopen("./logs/log.txt", "a");
    fprintf (pFile, "Reached Point 6\n");
    fclose (pFile); 

	TTF_Quit();
    
	pFile = fopen("./logs/log.txt", "a");
    fprintf (pFile, "Reached Point 7\n");
    fclose (pFile); 
	
	SDL_Quit();

    pFile = fopen("./logs/log.txt", "a");
    fprintf (pFile, "Game Closed Successfully\n");
    fclose (pFile);
}
