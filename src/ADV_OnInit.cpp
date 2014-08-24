#include "ADV.h"


bool AdvGame::OnInit() { 
	
	 if(SDL_Init(SDL_INIT_EVERYTHING) < 0 ){
         return false;
     }
	 
     if(TTF_Init() == -1) {
          return false;
     }
     
     GFXMODE::GFXMODE_Control.CHANGE_GFX_MODE(GFX_MODE_PC);
     
//     if((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
//         return false;
//     }

	 // create our main window
	 mpMainWindow = SDL_CreateWindow("Adventure",
		 SDL_WINDOWPOS_CENTERED,
		 SDL_WINDOWPOS_CENTERED,
		 640, 480,
		 SDL_WINDOW_OPENGL);

	 if (mpMainWindow == NULL)
	 {
		 return false;
	 }

	 // create the rendering context
	 mpRenderer = SDL_CreateRenderer(mpMainWindow, -1, SDL_RENDERER_PRESENTVSYNC);


     if(Player1.OnLoad("./images/pc_char-hi.bmp", 40, 40, false, false, 1) == false) {
         return false;
     }

	 InitializeItemList();
     
     CEntity::EntityList.push_back(&Player1);      //This adds the player character to the entity list... 
     Player1.posX = 6;
     Player1.posY = 6;

	 EnemyList.reserve(50);
     if(CArea::AreaControl.OnLoad("./maps/1.area") == false) {
         return false;
     }
     
     if (Enemy.OnLoad("./images/pc_001.bmp", 40, 40, false, false, 1) == false) {
         return false;
     }

     CEntity::EntityList.push_back(&Enemy);          //Put test enemy into Entity List
     Enemy.posX = 3;                                 //Set default enemy position.
     Enemy.posY = 3;

	 if (Enemy2.OnLoad("./images/pc_001.bmp", 40, 40, false, false, 1) == false) {
         return false;
     }
     CEntity::EntityList.push_back(&Enemy2);          //Put test enemy into Entity List
     Enemy2.posX = 10;                                 //Set default enemy position.
     Enemy2.posY = 2;

	 if (Enemy3.OnLoad("./images/pc_001.bmp", 40, 40, false, false, 1) == false) {
         return false;
     }
     CEntity::EntityList.push_back(&Enemy3);          //Put test enemy into Entity List
     
     Enemy3.posX = 11;                                 //Set default enemy position.
     Enemy3.posY = 9;

     

	 if (ActionControl.Messages.OnLoad() == false) {
	 	 return false;
	 }
     
	 if (Menu.OnLoad() == false ){
		 return false;
	 }

     //SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL * 5);     //This sets the option where if you hold down a key, it acts like you keep pressing it.
                        //1 = delay = how long you have to hold it down before it starts repeating in milliseconds
	                    //SDL_DEFAULT_REPEAT_INTERVAL * 5 = interval = how fast it repeats... in milliseconds (Default is build in SDL default... i *5'd it to slow it down.)
     CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
     CCamera::CameraControl.SetTarget(&Player1.posX, &Player1.posY);
     //SDL_WM_SetCaption("Adventure", NULL );
     ActionControl.OnLoad();
	 return true;
}
