#include "CArea.h"
#include "GFXMODE.h"
#include "Define.h"
#include "CFPS.h"
#include "ADV.h"
#include <stdio.h>
#include <time.h>
CArea  CArea::AreaControl;

CArea::CArea(){
     AreaSize = 0;
}

bool CArea::OnLoad(char* File) {
    MapList.clear();
	
	for (int i = 0; i < Game.EnemyList.size(); i++){
		Game.EnemyList[i].OnCleanup();
	}
	
	Game.EnemyList.clear();

	int Area_Enemy;
	int En_Num;
	char TilesetFile[255];
    
	FILE* pFileHandle = NULL;

	if(fopen_s( &pFileHandle, File, "r") )
	{
		return false;
    }
     
    fscanf_s(pFileHandle, "%s\n", TilesetFile, _countof(TilesetFile));
     
    if((Surf_Area_Tileset = CSurface::OnLoad(TilesetFile)) == false) {
		fclose(pFileHandle);
		return false;
    }

    fscanf_s(pFileHandle, "%d\n", &AreaSize);
    fscanf_s(pFileHandle, "%d:%d ", &Area_Enemy, &En_Num); //"x:y " X = types of enemies, y = number of enemies of type X
	 
	//Creates and pushes an new Enemy into Enemy List with with ID = Area_Enemy, En_Num times... 
	while (Area_Enemy != -1) {
		CEnemy Etemp;
		Etemp.ID = Area_Enemy;
		Etemp.EIGHTBITFILE = NULL;
		Etemp.PCIMAGE_FILE = NULL;
			for (int i = 0; i < En_Num; i++) {
				Game.EnemyList.push_back(Etemp);
			}
		fscanf_s(pFileHandle, "%d:%d ", &Area_Enemy, &En_Num);
	 }

	 fscanf_s(pFileHandle, "\n");

     for(int X = 0; X < AreaSize; X++) {
             for(int Y = 0; Y < AreaSize; Y++) {
                     char MapFile[255];
                     
                     fscanf_s(pFileHandle, "%s ", MapFile, _countof(MapFile));

                     CMap tempMap;
                     if(tempMap.OnLoad(MapFile) == false) {
                          fclose(pFileHandle);
                          return false;
                     }
                     
                     tempMap.Surf_Tileset = Surf_Area_Tileset;
                     
                     MapList.push_back(tempMap);
             }
             fscanf_s(pFileHandle, "\n");
     }
     
     fclose(pFileHandle);
     AreaControl.LoadEnemyList();
     return true;
}

void CArea::LoadEnemyList() {
	
	int EnemyQueue = 0;				//Total Number of enemies to load info for... starts at zero and should end at Enemylist.size()
	int TempID = 0;						//The Current Enemy ID we're looking for and working with.
	char EnemyInfo[255];			//The Buffer string to hold the crap

	while (EnemyQueue < Game.EnemyList.size()) {	//Start of main loop... should loop once for each Enemy ID/type of enemy.
		//FILE * LogFile = fopen("./logs/log.txt", "a");
		
		TempID = Game.EnemyList[EnemyQueue].ID;		//finds ID we're looking for
		
		//fprintf(LogFile, "TempID = %d\n", TempID);

		int NumEnemies = 0;	//Figures out how many enemies in the list have current ID
		int i = EnemyQueue;
		
		//fprintf(LogFile, "NumEnemies = %d\nEnemyQueue = %d\n", TempID, EnemyQueue);

		while ((i < Game.EnemyList.size()) && (Game.EnemyList[i].ID == TempID)){
			i++;
			NumEnemies++;
		}

		FILE* pEnemyFile = NULL;
		if (fopen_s(&pEnemyFile, "./data/Elist.data", "r"))
		{
			// Error loading enemies.
			// need to log and bail.
			return;
		}

		for (int i = 0; i < TempID; i++) {					//Go through file, line by line until you get to the line that is = TempID
			fscanf_s(pEnemyFile, "%s\n", EnemyInfo, _countof(EnemyInfo));//Each Line is One Enemy ID... so ID 1 = Line 2... line 0 = layout
			//fprintf(LogFile, "Enemyinfo = %s\n", EnemyInfo);
		}

		int TempID2 = 0; int HP = 0; int MP = 0; int AP = 0; int Experience = 0; int Gold = 0; int Attack = 0; int Defense = 0; int AttackPer = 0; int DefensePer = 0;int AttackSpeed = 0;int MoveSpeed = 0;int Item1 = 0;int Item2 = 0;int Item3 = 0;
		char EName[30];

		char PCImage_File[30];

		//               ID,Name hp mp ap at ap df dp as ms ex gp I1 I2 I3 PC
		fscanf_s(pEnemyFile, "%d:%s :%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%s \n", &TempID2, EName, _countof(EName), &HP, &MP, &AP, 
			&Attack, &AttackPer, &Defense, &DefensePer, &AttackSpeed, &MoveSpeed, &Experience, &Gold, &Item1, &Item2, &Item3, PCImage_File, _countof(PCImage_File));

		for (int i = EnemyQueue; i < NumEnemies; i++){
			Game.EnemyList[EnemyQueue].Name = EName;
			Game.EnemyList[EnemyQueue].Max_HP = HP;
			Game.EnemyList[EnemyQueue].Max_MP = MP;
			Game.EnemyList[EnemyQueue].Max_AP = AP;
			Game.EnemyList[EnemyQueue].ATT = Attack;
			Game.EnemyList[EnemyQueue].ATTPercent = AttackPer;
			Game.EnemyList[EnemyQueue].DEF = Defense;
			Game.EnemyList[EnemyQueue].DEFPercent = DefensePer;
			Game.EnemyList[EnemyQueue].ATT_SPEED = AttackSpeed;
			Game.EnemyList[EnemyQueue].MOV_SPEED = MoveSpeed;
			Game.EnemyList[EnemyQueue].ITEM1 = Item1;
			Game.EnemyList[EnemyQueue].ITEM2 = Item2;
			Game.EnemyList[EnemyQueue].ITEM3 = Item3;
			Game.EnemyList[EnemyQueue].PCIMAGE_FILE = *PCImage_File;
			EnemyQueue++;
		}
		fclose (pEnemyFile); 
		
	}//end of while loop

	// For Every Enemy in the list...
	for (int i = 0; i < Game.EnemyList.size(); i++){
		
		
		bool match = false;
		int x;
		srand(time(NULL));							//Find Unused Value for X, starting position within area
		do {
			x = rand() % (MAP_WIDTH * CArea::AreaControl.AreaSize);
			match = false;
			for (int i2 = 0; i2 < CEntity::EntityList.size(); i2++) {
				if (CEntity::EntityList[i2]->posX == x) {match = true;}
			}
		} while (match == true);
		Game.EnemyList[i].posX = x;

		do {										//Find Unused Y coordinate for starting position within area.
			x = rand() % (MAP_WIDTH * CArea::AreaControl.AreaSize);
			match = false;
			for (int i2 = 0; i2 < CEntity::EntityList.size(); i2++) {
				if (CEntity::EntityList[i2]->posY == x) {match = true;}
			}
		} while (match == true);
		Game.EnemyList[i].posY = x;
		//if (Game.EnemyList[i].OnLoad() == false){				//Finish Each Enemy's OnLoad Functionalities
		//	Game.ActionControl.QuickMessage("Error Loading Enemies...");
		//}
		CEntity::EntityList.push_back(&Game.EnemyList[i]);		//Put Enemy in the EntityList
	} //End of For Loop
}//end of function definition

void CArea::OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY) {
     switch (GFXMODE::GFXMODE_Control.GET_GFX_MODE()) {
          case (GFX_MODE_PC): {
               
               int FirstID = (-CameraX / MAP_WIDTH) + ((-CameraY / MAP_HEIGHT) * AreaSize);
               int ID;
               
               for(int i = 0; i < 4; i++) {
                       ID = FirstID + ((i / 2) * AreaSize) + (i % 2);
                      
                       int X = (CameraX % MAP_WIDTH) + ((i % 2) * MAP_WIDTH);   //The X Coordinate of Where to start drawing the map.
                       //  x equals CameraX CameraX mod Mapwidth, cause if CameraX is larger than 40, we don't want it to draw it that far away...
                       //  Then for the other three maps i = 1, 2, 3, So i=1 is the map to the right of the first one, so draw it at the same location
                       //  but offset it by the Map_Width... but i % 2 gives the pattern 0, 1, 0, 1, so its only on the odd maps... the ones to the right.
                       int Y = (CameraY % MAP_HEIGHT) + ((i / 2) * MAP_HEIGHT);
                       // Same thing but i / 2 gives the pattern 0, 0, 1, 1 so its only for the maps below the first two...
                                     
                       MapList[ID].OnRender(Surf_Display, X, Y);
               }
               break;

          }
          case (GFX_MODE_8BIT): {
               int MapWidth = MAP_WIDTH * TILE_SIZE;
               int MapHeight = MAP_HEIGHT * TILE_SIZE;
     
               int FirstID = -CameraX / MapWidth;
                   FirstID = FirstID + ((-CameraY / MapHeight) * AreaSize);
         
               for(int i = 0; i < 4; i ++) {
                       int ID = FirstID + ((i / 2) * AreaSize) + (i %2);
             
                       if (ID < 0 || ID >= MapList.size()) continue;
             
                       int X = ((ID % AreaSize) * MapWidth) + CameraX;
                       int Y = ((ID / AreaSize) * MapHeight) + CameraY;
             
                       MapList[ID].OnRender(Surf_Display, X, Y);
               }
               break;
          }

          default: {
          }
     }
}

void CArea::OnCleanup() { 
	if(Surf_Area_Tileset) {
         SDL_FreeSurface(Surf_Area_Tileset);
    } 

    for(int i = 0; i < MapList.size(); i++) {
		MapList[i].OnCleanup();
    }
	 
    MapList.clear(); 
}

CMap* CArea::GetMap(int X, int Y) {
      
      int ID = X / MAP_WIDTH;
      
      ID = ID + ((Y / MAP_HEIGHT) * AreaSize);
      
      if(ID < 0 || ID >= MapList.size()) {
            return NULL;
      }
      /*
      FILE * pFile;
      pFile = fopen("./logs/log.txt", "a");
      fprintf (pFile, "CArea::GetMap... X = %d, Y = %d, ID = %d\n", X, Y, ID);
      fclose (pFile);
      */
      return &MapList[ID];
}

MTile* CArea::GetTile(int X, int Y) {      
      CMap* Map = GetMap(X, Y);
      
      if(Map == NULL) return NULL;
      
      X = X % MAP_WIDTH;
      Y = Y % MAP_HEIGHT;
      /*
      FILE * pFile;
      pFile = fopen("./logs/log.txt", "a");
      fprintf (pFile, "CArea::GetTile.. X = %d, Y = %d\n", X, Y);
      fclose (pFile);
      */
      return Map->GetTile(X, Y);      
}


