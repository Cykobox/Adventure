#ifndef _CCAMERA_H_
        #define _CCAMERA_H_

//#include <SDL.h>

enum {
     TARGET_MODE_NORMAL = 0,
     TARGET_MODE_CENTER
};

class CCamera {
      public:
             static CCamera CameraControl;
      public:
              
              int X;                             //The X coordinate, in tiles of the upper left hand corner of the screen
              int Y;                             //The Y coordinate, in tiles of the upper left hand corner of the screen
              
              int* TargetX;
              int* TargetY;
      
      public:
             int TargetMode;
      public:
             CCamera();
             void OnMove(int MoveX, int MoveY);
             int GetX();
             int GetY();
             
             void SetPos(int X, int Y);
             void SetTarget(int* X, int* Y);
};

#endif
