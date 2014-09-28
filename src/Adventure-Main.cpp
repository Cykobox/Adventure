#include <cstdlib>
#include <iostream>
#include <SDL.h>
#include "ADV.h"

AdvGame::AdvGame() :
	mpMainWindow(NULL),
	mpRenderer(NULL)
{
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

//
// Empties the list of active enemies, despawning any that are active.
void AdvGame::EmptyEnemyList()
{
	std::vector<CEnemy>::iterator it;
	for (it = EnemyList.begin(); it != EnemyList.end(); ++it)
	{
		(*it).OnCleanup();
	}

	EnemyList.clear();
}


AdvGame Game;

int main(int argc, char *argv[])
{
	std::cout << "Main start\n";
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif
	Game.OnExecute();

	//system("PAUSE");
	return false;
}
