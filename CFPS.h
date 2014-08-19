#ifndef _CFPS_H_
     #define _CFPS_H_

#include <SDL.h>

class CFPS {
      public:
             static CFPS FPSControl;
      private:
              int OldTime;
              int LastTime;
              
              float SpeedFactor;
              
              int NumFrames;             //the number of frames per second.
              int Frames;                //counte for how many frames this second
      public:
             CFPS();
             void OnLoop();
             
             int GetFPS();
             float GetSpeedFactor();
};

#endif
