#ifndef _CENEMY_H_
    #define _CENEMY_H_
 
#include "CEntity.h"

class CEnemy : public CEntity {
      public:
             CEnemy();
             
			 int ID;

             std::string Name; //Enemy's Name
             int Max_HP;     //Enemy's Maximum Hit Points
             int Cur_HP;     //Enemy's Current Hit Points
             int Max_MP;     //Enemies Maximum Magic Points
             int Cur_MP;     //Enemies Current Magic Points
             int Max_AP;     //Enemies Maximum Ability Points
             int Cur_AP;     //Enemies Current Ability Points
             
             int ATT;		  //The Enemy's Attack Power
             int ATTPercent;  //Attack Percentage
			 int DEF;		  //The Enemy's Defense Power
             int DEFPercent;  //Dodge/Defense Percentage
			 int ATT_SPEED;   //How fast the enemy attacks (How many ticks before it attacks again.)
             int MOV_SPEED;   //How fast the enemy moves, (how many ticks have to happen before it can move again.) range 333 and up, lower = faster
             
             int EXP;         //How many experience point are awarded when its killed
             int GOLD;        //How much gold are rewarded on its defeat
             int ITEM1;       //Common item reward after its defeat
             int ITEM2;       //Uncommon item reward
             int ITEM3;       //Rare item reward 

			 //Movement Variables
			 int LastMove;    //the ticks count the last time the enemy moved


			 //Image and model files:
			 char PCIMAGE_FILE;
			 char EIGHTBITFILE;

             bool OnLoad(char* File, int Width, int Height, bool Animate, bool Transparency, int MaxFrames);
             bool OnLoad();
			 void MoveCheck();
			 void Death();
			 void OnLoop();
             void OnRender(SDL_Surface* Surf_Display);
             void OnCleanup();
             void OnAnimate();
             void OnCollision(CEntity* Entity);
             void HPCheck();
};

#endif
