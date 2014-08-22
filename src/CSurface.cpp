
#include "CSurface.h"

CSurface::CSurface() {                    

}

SDL_Surface* CSurface::OnLoad(char* File) {
     SDL_Surface* Surf_Temp = NULL;
     SDL_Surface* Surf_Return = NULL;
     
     if((Surf_Temp = SDL_LoadBMP(File)) == NULL) {
          return NULL;
     }
     
     //Surf_Return = SDL_DisplayFormat(Surf_Temp);
     SDL_FreeSurface(Surf_Temp);
     
     return Surf_Return;
}

bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y) {
     if (Surf_Dest == NULL || Surf_Src == NULL) {
         return false;
     }
     
     SDL_Rect DestR;   //defines a sdl Rectrangle named DestR
     
     DestR.x = X;      //DestR.x is the x value, where on the horizontal plane, to draw the image
     DestR.y = Y;      //DestR.y is the y value, where on the vertical line, to draw the image
          
     SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);
     return true;
}

bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H) {
     if (Surf_Dest == NULL || Surf_Src == NULL) { 
         return false;
     }
     
     SDL_Rect DestR;
     
     DestR.x = X;       //defines, where on the x axis of the destination image to draw the new image
     DestR.y = Y;       //defines, where on the y axis of the destination image to draw the new image
     
     SDL_Rect SrcR;
     
     SrcR.x = X2;       //defines, where on the x axis of the source image do we want to copy over, to take to the new image
     SrcR.y = Y2;       //defines, where on the y axis of the source image to start from, to copy over to the new image
     SrcR.w = W;        //Defines  the width of the image to copy over, Starting from SrcR.x
     SrcR.h = H;        //defines, the height of the image to copy over, starting from SrcR.y
     
     SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);  //Notice the second parameter is no longer NULL, but a pointer to the src
     return true;
}

bool CSurface::Transparent(SDL_Surface* Surf_Dest, int R, int G, int B) {
     if(Surf_Dest == NULL) {
          return false;             
     }

     //SDL_SetColorKey(Surf_Dest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(Surf_Dest->format, R, G, B));
     
     return true;
}


