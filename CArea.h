#ifndef _CAREA_H_
        #define _CAREA_H_

#include "CMap.h"

class CArea {
      public: 
            static CArea          AreaControl;
			  
      public:
            std::vector<CMap>     MapList;
			int                   AreaSize;          //size of the area in maps...
      private:
              
              
            SDL_Surface*           Surf_Area_Tileset;
              
              
      public:
            CArea();
            bool OnLoad(char* File);
            void LoadEnemyList();
			void OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY);
            void OnCleanup();
             
      public:
            CMap*  GetMap(int X, int Y);
            MTile* GetTile(int X, int Y);
};

#endif
