#include "CArea.h"
#include "GFXMODE.h"
#include "Define.h"
//#include "CFPS.h"
//#include "ADV.h"
//#include <stdio.h>
//#include <time.h>
#include "StringUtils.h"
#include "tinyXML\tinyxml2.h"


CArea  CArea::AreaControl;

CArea::CArea()
: mSizeX(0)
, mSizeY(0)
, mBackgroundTileID(0)
, mpTileMap(NULL)
{

}

CArea::~CArea()
{
	if (mpTileMap)
	{
		delete[] mpTileMap;
	}
}

bool CArea::OnLoad(SDL_Renderer *pRenderer, char* fileName)
{
	// load XML 'filename', and then set up our data with that information
	FILE *pXMLFile = NULL;
	std::string sFilename = std::string("./data/areas/") + fileName;
	if (fopen_s(&pXMLFile, sFilename.c_str(), "rb"))
	{
		// Log( "Could not open tileset XML file");
		return false;
	}

	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(pXMLFile) != tinyxml2::XML_NO_ERROR)
	{
		// Log("Error parsing Tileset XML file.");
		fclose(pXMLFile);
		return false;
	}

	// File has been parsed, we no longer need it open.
	fclose(pXMLFile);

	// start yanking data out of our XML.
	tinyxml2::XMLElement *pRoot = doc.FirstChildElement("area"); // the <tileset> element
	tinyxml2::XMLElement *pNameElem = NULL; // the <name> element
	tinyxml2::XMLElement *pTileSetElem = NULL; // the <tileSet> element
	tinyxml2::XMLElement *pSizeXElem = NULL; // the <sizeX> element
	tinyxml2::XMLElement *pSizeYElem = NULL; // the <sizeY> element
	tinyxml2::XMLElement *pBGIDElem = NULL; // the <backgroundTileID> element
	tinyxml2::XMLElement *pMapDataElem = NULL; // the <mapData> element
	if (pRoot)
	{
		pNameElem = pRoot->FirstChildElement("name");
		pTileSetElem = pRoot->FirstChildElement("tileset");
		pSizeXElem = pRoot->FirstChildElement("sizeX");
		pSizeYElem = pRoot->FirstChildElement("sizeY");
		pBGIDElem = pRoot->FirstChildElement("bgTileID");
		pMapDataElem = pRoot->FirstChildElement("mapData");
	}

	if (!pNameElem || !pTileSetElem || !pSizeXElem || !pSizeYElem || !pBGIDElem || !pMapDataElem)
	{
		// Error, not a valid Area XML.
		return false;
	}

	// Set our name:
	mName = pNameElem->GetText();

	// load our tileset.
	std::string sTileSet = pTileSetElem->GetText();
	sTileSet = sTileSet + ".xml";
	if (!mTileSet.Load(pRenderer, sTileSet))
	{
		// Error: Couldn't load tileset
		return false;
	}

	// get our background tile ID, and the size of the map.
	pSizeXElem->QueryIntText(&mSizeX);
	pSizeYElem->QueryIntText(&mSizeY);
	pBGIDElem->QueryIntText(&mBackgroundTileID);

	// Total size of the map in tiles.
	int totalTiles = mSizeX*mSizeY;

	if (totalTiles <= 0)
	{
		// Error, map with 0 size
		return false;
	}

	// allocate our map memory
	mpTileMap = new int[totalTiles];

	// load our data rows.
	tinyxml2::XMLElement *pRow = pMapDataElem->FirstChildElement();
	int tileCount = 0; // count the number of tiles to make sure it matches.
	std::vector<std::string> subStrs;
	int curIdx = 0;
	while (pRow && curIdx < totalTiles)
	{
		subStrs.clear();

		std::string sRowData = pRow->GetText();

		SplitString(subStrs, sRowData, " ");

		for (auto it = subStrs.begin(); it != subStrs.end(); ++it)
		{
			int num = StringToNumber<int>(*it);
			mpTileMap[curIdx] = num;
			++curIdx;

			if (curIdx > totalTiles)
			{
				// ERROR. Too many tiles in the XML
				// bail so we don't overflow the array
				break;
			}
		}

		pRow = pRow->NextSiblingElement();
	}

	if (curIdx < totalTiles)
	{
		// Error: Not enough tiles in the XML
		return false;
	}


	return true;


	//MapList.clear();

	//	int Area_Enemy;
	//	int En_Num;
	//	char TilesetFile[255];

	//	FILE* pFileHandle = NULL;

	//	if(fopen_s( &pFileHandle, File, "r") )
	//	{
	//		return false;
	//    }

	//    fscanf_s(pFileHandle, "%s\n", TilesetFile, _countof(TilesetFile));

	//    if((Surf_Area_Tileset = CSurface::OnLoad(TilesetFile)) == false) {
	//		fclose(pFileHandle);
	//		return false;
	//    }

	//    fscanf_s(pFileHandle, "%d\n", &AreaSize);
	//    fscanf_s(pFileHandle, "%d:%d ", &Area_Enemy, &En_Num); //"x:y " X = types of enemies, y = number of enemies of type X

	//Creates and pushes an new Enemy into Enemy List with with ID = Area_Enemy, En_Num times... 
	//	while (Area_Enemy != -1) {
	//		CEnemy Etemp;
	//		Etemp.ID = Area_Enemy;
	//		Etemp.EIGHTBITFILE = NULL;
	//		Etemp.PCIMAGE_FILE = NULL;
	//			for (int i = 0; i < En_Num; i++) {
	//				Game.EnemyList.push_back(Etemp);
	//			}
	//		fscanf_s(pFileHandle, "%d:%d ", &Area_Enemy, &En_Num);
	//	 }

	//	 fscanf_s(pFileHandle, "\n");

	/*
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
	*/

	//     fclose(pFileHandle);
	//     AreaControl.LoadEnemyList();
	//     return true;
}

void CArea::LoadEnemyList() {
	/*
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
	*/

}//end of function definition

void CArea::OnRender(SDL_Renderer *pRenderer)
{
	switch (GFXMODE::GFXMODE_Control.GET_GFX_MODE())
	{
	case (GFX_MODE_PC) :
	{
		// loop over all tilesets on the screen, and render them into their proper place.
		// For testing now, just start with tile 0,0 in the upper left and render them all from there.

		// WHat tile is in the upper left of the screen.
		// This will eventually need to be filled in with data from the camera as the player moves around.
		int startX = -1;
		int startY = -1;

		int ix = startX;
		int iy = startY;
		int screenX = 0;
		int screenY = 0;

		while (screenX < PC_WIDTH_TILES) // TODO -- 10 = number of tiles wide the screen is.
		{
			while (screenY < PC_HEIGHT_TILES) // TODO -- 10 = number of tiles tall the screen is.
			{
				// default to the BG tile ID.
				int tileID = mBackgroundTileID;
				if (ix >= 0 && ix < mSizeX && iy >= 0 && iy < mSizeY)
				{
					// if this is in the map, then look up the tileID for it.
					tileID = mpTileMap[(iy * mSizeX) + ix];
				}

				// draw the tile at ix, iy.
				mTileSet.Render(tileID, screenX*TILE_SIZE, screenY*TILE_SIZE, TILE_SIZE, TILE_SIZE);


				// move to next tile
				++iy;
				++screenY;
			}

			// go to next row:
			++ix;
			++screenX;
			iy = startY;
			screenY = 0;
		}

		break;

	}
	case (GFX_MODE_8BIT) :
	{
		break;
	}

	default:
		break;
	}
}

void CArea::OnCleanup() {
	//if(Surf_Area_Tileset) {
	//     SDL_FreeSurface(Surf_Area_Tileset);
	//} 
}

//
// Returnds whether the given space is a walkable space.
bool CArea::IsWalkable(int X, int Y)
{
	return true;
}

void CArea::SpawnEnemy(std::vector<CEnemy> &EnemyList)
{
	// TODO - Enemy spawning moves here.
	// This will ensure that enemies only spawn in valid locations,
	// and proper enemies spawn for the area the player is in.
}
