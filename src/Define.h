#ifndef _DEFINE_H_
        #define _DEFINE_H_

#define MAP_WIDTH   40  //The Width of each map, in tiles, in an area
#define MAP_HEIGHT  40  //The Height of each map, in tiles, in an area
#define TILE_SIZE   40  //The size, in pixels of a tile, square

#define WWIDTH      800  //width of screen used to be 640
#define WHEIGHT     600  //height of screen

#define PC_WIDTH_TILES (WWIDTH / TILE_SIZE)
#define PC_HEIGHT_TILES (WHEIGHT / TILE_SIZE)

enum {
     GFX_MODE_PC = 1,
     GFX_MODE_8BIT,
     GFX_MODE_16BIT,
     GFX_MODE_64BIT,
     GFX_MODE_PS2,
     GFX_MODE_CURRENT
};

#endif
