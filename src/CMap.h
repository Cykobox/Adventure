#ifndef _CMAP_H_
        #define _CMAP_H_

#include <SDL.h>
#include <vector>

#include "MTile.h"
#include "CSurface.h"

class CMap {
	public:
		CMap();
		bool OnLoad(char* File);
		void OnRender(SDL_Surface* Surf_Display, int MapX, int MapY);
		MTile* GetTile(int X, int Y);
		void OnCleanup();

		SDL_Surface* Surf_Tileset;
	private:
		std::vector<MTile> TileList;
};

#endif
