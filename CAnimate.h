#ifndef _CANIMATE_H_
        #define _CANIMATE_H_

//#include <SDL.h>

class CAnimation {
      private:
              int CurrentFrame;
              int FrameInc;    //Frame Incriment This is wither +1 or -1, which is how much we are incimenting the frame by (-1 used in oscilation)
      
      private:
              int FrameRate;   // milliseconds
              long OldTime;    // last time a frame was draw, in milliseconds
      
      public:
             int MaxFrames;
             bool Oscillate;   // Switch to oscillate or not
      
      public:
             CAnimation();
             void OnAnimate();
      
      public:
             void SetFrameRate(int Rate);
             void SetCurrentFrame(int Frame);
             int GetCurrentFrame();
};

#endif
