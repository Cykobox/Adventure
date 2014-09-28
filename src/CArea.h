//
// CArea
//
// Responsibilities - Contains all information about one "map" of the game.
// renders tiles to the screen, contains information about where players and enemies can move
// and what enemies can spawn where.


#ifndef _CAREA_H_
#define _CAREA_H_

#include "CEnemy.h"
#include "TileSet.h"
#include <SDL.h>

class CArea
{
	public: 
		CArea();
		~CArea();
		bool OnLoad(SDL_Renderer *pRenderer, char* File);
		void LoadEnemyList();
		void OnRender(SDL_Renderer *pRenderer);
		void OnCleanup();

		bool IsWalkable(int X, int Y);

		void SpawnEnemy(std::vector<CEnemy> &EnemyList);

		static CArea          AreaControl;
			  
	private:
		int* 					mpTileMap; // the map data. An array of TileIDs of size mSizeX * mSizeY.
		std::string				mName;
		int						mSizeX; // Area X size in tiles.
		int						mSizeY; // Area Y size in tiles.
		int						mBackgroundTileID; // The ID of the tile to use for any areas "off the map" that end up on screen
		TileSet					mTileSet; // Todo - Move this to a Tileset manager class?
};

#endif
