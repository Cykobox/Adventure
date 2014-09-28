//
// TileSet.cpp
// (c) Christopher Bauer 2014
//
// Responsibilities: Own a tileset, and render tiles to the screen at specific coordinates.
//

#include "TileSet.h"
#include "tinyXML\tinyxml2.h"
#include <SDL_image.h>


TileSet::TileSet()
{

}

TileSet::~TileSet()
{

}

bool TileSet::Load(SDL_Renderer *pRenderer, std::string Filename)
{
	// load XML 'filename', and then set up our data with that information

	FILE *pXMLFile = NULL;
	std::string sFileName = std::string(".\\data\\tilesets\\") + Filename;
	if (fopen_s(&pXMLFile, sFileName.c_str(), "rb"))
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
	tinyxml2::XMLElement *pRoot = doc.FirstChildElement("tileset"); // the <tileset> element
	tinyxml2::XMLElement *pNameElem = NULL; // the <name> element
	tinyxml2::XMLElement *pTexElem = NULL; // the <texture> element
	tinyxml2::XMLElement *pTilesElem = NULL; // the <tiles> element
	tinyxml2::XMLElement *pSizeElem = NULL; // the <tileZSize> element
	if (pRoot)
	{
		pNameElem = pRoot->FirstChildElement("name");
		pTexElem = pRoot->FirstChildElement("texture");
		pTilesElem = pRoot->FirstChildElement("tiles");
		pSizeElem = pRoot->FirstChildElement("tileSize");
	}

	if (!pNameElem || !pTexElem || !pTilesElem || !pSizeElem)
	{
		// Error, not a valid tileset XML.
		return false;
	}

	// Set our name:
	mName = pNameElem->GetText();

	// Set our tile size:
	pSizeElem->QueryIntText(&mTileSize);

	// load our texture:
	std::string texPath = std::string("./data/tilesets/") + pTexElem->GetText();
	if (!mTexture.Load(pRenderer, texPath))
	{
		// error couldn't load texture
		return false;
	}

	// set up our tiles.
	tinyxml2::XMLElement *pTile = pTilesElem->FirstChildElement();
	while (pTile)
	{
		tinyxml2::XMLElement *pTID = pTile->FirstChildElement("tileID");
		tinyxml2::XMLElement *pTName = pTile->FirstChildElement("name");
		tinyxml2::XMLElement *pTposX = pTile->FirstChildElement("posX");
		tinyxml2::XMLElement *pTposY = pTile->FirstChildElement("posY");
		tinyxml2::XMLElement *pTWalk = pTile->FirstChildElement("walkable");

		if (pTID && pTName && pTposX && pTposY && pTWalk)
		{
			STile tile;
			tile.name = pTName->GetText();
			pTposX->QueryIntText(&tile.posX);
			pTposY->QueryIntText(&tile.posY);
			pTWalk->QueryBoolText(&tile.walkable);

			int tileID = -1;
			pTID->QueryIntText(&tileID);

			if (tileID <= 0)
			{
				// error invalid tile ID.
			}
			else
			{
				auto it = mTileMap.find(tileID);
				if (it != mTileMap.end())
				{
					// Error, Duplicate tile ID found.
				}
				else
				{
					mTileMap[tileID] = tile;
				}
			}
		}
		else
		{
			// Error parsing a tile element.
		}

		pTile = pTile->NextSiblingElement();
	}

	return true;

}

void TileSet::Render(int tileID, int X, int Y, int width, int height)
{
	const std::map<int,STile>::iterator it = mTileMap.find(tileID);
	if (it != mTileMap.end())
	{
		// render!
		mTexture.Render(X, Y, width, height, it->second.posX * mTileSize, it->second.posY * mTileSize, mTileSize, mTileSize);
	}

}
