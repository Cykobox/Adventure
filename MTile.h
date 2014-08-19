#ifndef _MTILE_H_
        #define _MTILE_H_

enum {
     TILE_TYPE_NONE = 0,
     TILE_TYPE_NORMAL,
     TILE_TYPE_BLOCK
     };

class MTile {
      public:
             int TileID;
             int TypeID;
             MTile();
};

#endif
