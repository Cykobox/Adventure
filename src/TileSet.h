//
// TileSet.h
// (c) Christopher Bauer 2014
//
// Responsibilities: Own a tileset, and render tiles to the screen at specific coordinates.
//

#ifndef _TILESET_H_
#define _TILESET_H_

#include <string>
#include <map>
#include "Texture.h"

class TileSet
{
public:
	TileSet();
	~TileSet();

	bool Load(SDL_Renderer *pRenderer, std::string Filename);

	void Render(int tileID, int X, int Y, int width, int height) const;

	bool IsWalkable(int tileID);

private:
	struct STile
	{
		int posX;
		int posY;
		std::string name;
		bool walkable;
	};
	typedef std::map< int, STile> TTileMap;

	std::string mName;
	Texture mTexture;
	int mTileSize;

	TTileMap mTileMap;
};

#endif
