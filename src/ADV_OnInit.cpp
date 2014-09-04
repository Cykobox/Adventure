#include "ADV.h"


bool AdvGame::OnInit() { 
	
	 if(SDL_Init(SDL_INIT_EVERYTHING) < 0 ){
         return false;
     }
	 
     if(TTF_Init() == -1) {
          return false;
     }
     
     GFXMODE::GFXMODE_Control.CHANGE_GFX_MODE(GFX_MODE_PC);
     
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
	 mpRenderer = SDL_CreateRenderer(mpMainWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	 
	 /*SDL_RenderSetLogicalSize(mpRenderer, 1080, 720);  
	 I think this is the code that needs to be added so that it all renders to HD 
	 and the larger resolution but then it gets down rezzed to whatever the window
	 size is... i think... but I'm not sure. 
	 */
     
	 if(Player1.OnLoad(mpRenderer, "./images/pc_char-hi.bmp", 40, 40, false, false, 1) == false) {
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
     
	 if (Enemy.OnLoad(mpRenderer, "./images/pc_001.bmp", 40, 40, false, false, 1) == false) {
         return false;
     }

     CEntity::EntityList.push_back(&Enemy);          //Put test enemy into Entity List
     Enemy.posX = 3;                                 //Set default enemy position.
     Enemy.posY = 3;

	 if (Enemy2.OnLoad(mpRenderer, "./images/pc_001.bmp", 40, 40, false, false, 1) == false) {
         return false;
     }
     CEntity::EntityList.push_back(&Enemy2);          //Put test enemy into Entity List
     Enemy2.posX = 10;                                 //Set default enemy position.
     Enemy2.posY = 2;

	 if (Enemy3.OnLoad(mpRenderer, "./images/pc_001.bmp", 40, 40, false, false, 1) == false) {
         return false;
     }
     CEntity::EntityList.push_back(&Enemy3);          //Put test enemy into Entity List
     
     Enemy3.posX = 11;                                 //Set default enemy position.
     Enemy3.posY = 9;

     ActionControl.OnLoad();

	 if (ActionControl.Messages.OnLoad(mpRenderer) == false) {
	 	 return false;
	 }
	 ActionControl.Messages.AddMessage("Welcome to Adventure! w,a,s,d = Move, SpaceBar = Menu, Num Pad2 = Action", 0, 0, 0);
	 if (Menu.OnLoad(mpRenderer, 600, 160, 0, 0) == false ){ // don't know if this is the right place to put the Menu... but just trying to put it on the screen.
	 	 return false;
	 }

     //SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL * 5);     //This sets the option where if you hold down a key, it acts like you keep pressing it.
                        //1 = delay = how long you have to hold it down before it starts repeating in milliseconds
	                    //SDL_DEFAULT_REPEAT_INTERVAL * 5 = interval = how fast it repeats... in milliseconds (Default is build in SDL default... i *5'd it to slow it down.)
     CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
     CCamera::CameraControl.SetTarget(&Player1.posX, &Player1.posY);
     
	 return true;
}
