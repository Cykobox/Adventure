#include "CMap.h"
#include "GFXMODE.h"
#include "Define.h"

CMap::CMap(){
     Surf_Tileset = NULL;
}

bool CMap::OnLoad(char* File) {
     TileList.clear();
     
     FILE* FileHandle = fopen(File, "r");
     
     if(FileHandle == NULL) {
          return false;
     }
     
     for(int Y = 0;Y < MAP_HEIGHT; Y++) {
             for(int X = 0; X < MAP_WIDTH; X++) {
                   MTile tempTile;
                   
                   fscanf(FileHandle, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);
                   
                   TileList.push_back(tempTile);
             }
             fscanf(FileHandle, "/n");
     }
     fclose(FileHandle);
     
     return true;

}

void CMap::OnRender(SDL_Surface* Surf_Display, int MapX, int MapY) {

     switch (GFXMODE::GFXMODE_Control.GET_GFX_MODE()) {     
          case (GFX_MODE_PC): {
     
               /* MapX and MapY are the offsets of where to stat drawing the map, from the camera... ie, if the camera is at position 1, 1
                  then the MapX and MapY will be -1, -1, because the map needs to be drawn starting at location -1, -1) */
               
               if(Surf_Tileset == NULL) return;
               
               int TilesetWidth = Surf_Tileset->w / TILE_SIZE; //figure out how many tiles wide the tile set is
               int TilesetHeight = Surf_Tileset->h / TILE_SIZE; // figure out how many tiles high the tile set is              
               
               int ID = 0;

               for(int Y = 0;Y < MAP_HEIGHT;Y++) {   //beginning of loop for the height axis, up and down
                       for(int X = 0;X < MAP_WIDTH;X++) {   //beginning of the loop from left to right
                               if(TileList[ID].TypeID == TILE_TYPE_NONE) {   // if the tile TYPE of the tile is 0, then don't draw anything
                                    ID++;                                    // but incriment the ID by one to move to the next tile in the tileset
                                    continue;
                               }
                     
                               int DrawX = (MapX + X) * TILE_SIZE;  //New Variable, which tells us where on the screen to draw... since we are only drawing what on screen
                                                       //we take the first ID to be draw, which is determined above, and start at the beginning point on the screen
                                                       //which is 0, 0, which is our current X and Y for our for functions... Multiply those by the TILE_SIZE to get exactly where on the screen to draw
                               int DrawY = (MapY + Y) * TILE_SIZE;  //same thing for Y 
                     
                               int TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_SIZE;   //This is suppose to figure out where int he tileset to grab the tile from, based on the Tile ID... but I don't get it.
                               int TilesetY = (TileList[ID].TileID / TilesetWidth) * TILE_SIZE;   //it takes the tile ID... not the tile type, and uses that to calculate the spot, since the tile TYPE cannot be zero, the tile ID can be
                     
                               CSurface::OnDraw(Surf_Display, Surf_Tileset, DrawX, DrawY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);  //Draws the bitch, based on the coordinate, NOTE: This draw it directly to Surf_Display, also, it draws everything, even tiles who are off screen.

                               ID++;
                       }
               }
               break;
          }     
          case (GFX_MODE_8BIT): {
               if(Surf_Tileset == NULL) return;    //if the tileset doesn't contain anything, exit out

               int TilesetWidth = Surf_Tileset->w / TILE_SIZE; //figure out how many tiles wide the tile set is
               int TilesetHeight = Surf_Tileset->h / TILE_SIZE; // figure out how many tiles high the tile set it
     
               int ID = 0;
     
               for(int Y = 0;Y < MAP_HEIGHT;Y++) {   //beginning of loop for the height axis, up and down
                       for(int X = 0;X < MAP_WIDTH;X++) {   //beginning of the loop from left to right
                               if(TileList[ID].TypeID == TILE_TYPE_NONE) {   // if the tile TYPE of the tile is 0, then don't draw anything
                                    ID++;                                    // but incriment the ID by one to move to the next tile in the tileset
                                    continue;
                               }
                     
                               int tX = MapX + (X * TILE_SIZE);              //new variable, tX, which is equal to MapX, which is the offset from 0,0 sent to us in the function call
                                                                   //plus which every tile we are on, (X * tilesize)
                               int tY = MapY + (Y * TILE_SIZE);              // same thing for the height 
                     
                               int TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_SIZE;   //This is suppose to figure out where int he tileset to grab the tile from, based on the Tile ID... but I don't get it.
                               int TilesetY = (TileList[ID].TileID / TilesetWidth) * TILE_SIZE;   //it takes the tile ID... not the tile type, and uses that to calculate the spot, since the tile TYPE cannot be zero, the tile ID can be
                     
                               CSurface::OnDraw(Surf_Display, Surf_Tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);  //Draws the bitch, based on the coordinate, NOTE: This draw it directly to Surf_Display, also, it draws everything, even tiles who are off screen.
                               
                               ID++;
                       }
               }
               break;
          }
          default: {
          }
     }
}

MTile* CMap::GetTile(int X, int Y) {
       int ID = 0;
       
       ID = X;
       ID = ID + (MAP_WIDTH * Y);
       
       if(ID < 0 || ID >= TileList.size()) {
             return NULL;
       }
       
       return &TileList[ID];
}

void CMap::OnCleanup() {
    //It locks up here when you close the game... but I don't know why.
	//I think its because Surf_tileset has already been freed... but I don't know why, how, or where.

	SDL_FreeSurface(Surf_Tileset);
}












