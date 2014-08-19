#ifndef _GFXMODE_H_
        #define _GFXMODE_H_

class GFXMODE {
      public:
             static GFXMODE GFXMODE_Control;
             int GFX_MODE;
      public:
             GFXMODE();
             int GET_GFX_MODE();
             void CHANGE_GFX_MODE(int NEW_MODE);
};
#endif
