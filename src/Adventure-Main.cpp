#include <cstdlib>
#include <SDL.h>
#include "ADV.h"

AdvGame::AdvGame() {
    Surf_Display = NULL;
    Menu_Vis = true;
    Running = true;
	Pause = false;

}

int AdvGame::OnExecute(){
	if(OnInit() == false) {
        return -1;
    }
     
	SDL_Event Event;
    
	while (Running) {
    
		while(SDL_PollEvent(&Event)) {
			OnEvent(&Event);
			
			}
			
			OnLoop();
			
			OnRender();
			
    }

    OnCleanup();
    return 0;
}

void AdvGame::Reset() {
     
}

AdvGame Game;

int main(int argc, char *argv[])
{
	printf("Main start\n");
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif
	return Game.OnExecute();
	
}
