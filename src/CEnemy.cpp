#include "CEnemy.h"
#include <time.h>
#include "ADV.h"
#include <string>
#include <sstream>

CEnemy::CEnemy() {
     Type = ENTITY_TYPE_ENEMY;  
}

bool CEnemy::OnLoad(SDL_Renderer *pRenderer) {
	if (CEntity::OnLoad(pRenderer, &PCIMAGE_FILE, TILE_SIZE, TILE_SIZE, false, false, 0) == false){
		return false;
	}
	Cur_HP = Max_HP;
	Cur_MP = Max_HP;
	Cur_AP = Max_AP;
	Dead = false;
	Width = Height = TILE_SIZE;
	Type = ENTITY_TYPE_ENEMY;

	return true;
}
bool CEnemy::OnLoad(SDL_Renderer *pRenderer, char* File, int Width, int Height, bool Animate, bool Transparency, int MaxFrames) {
	if (CEntity::OnLoad(pRenderer, File, Width, Height, Animate, Transparency, MaxFrames) == false) {
          return false;
     }
	 Name = "Skeleton";
     MOV_SPEED = 800;
	 LastMove = SDL_GetTicks();
	 Max_HP = 250;
	 Cur_HP = Max_HP;
	 Max_MP = 25;
	 Cur_MP = Max_HP;
	 Max_AP = 25;
	 Cur_AP = Max_AP;
	 ATT = 5;
	 ATTPercent = 5;
	 DEF = 10;
	 DEFPercent = 5;
	 EXP = 3;
	 GOLD = 2;
	 ITEM1 = 0;
	 ITEM2 = 1;
	 ITEM3 = 2;

     return true;
}

void CEnemy::OnLoop() {
    MoveCheck(); 
	CEntity::OnLoop();
}

void CEnemy::OnRender(SDL_Renderer *pRenderer) {
     CEntity::OnRender(pRenderer);
}

void CEnemy::OnCleanup(){
     CEntity::OnCleanup();
}

void CEnemy::OnCollision(CEntity* Entity) {
}

void CEnemy::OnAnimate() {

}

void CEnemy::HPCheck() {
	if (Cur_HP > Max_HP) Cur_HP = Max_HP;
	if (Cur_HP <= 0) Death();
}

void CEnemy::Death() {

	std::ostringstream s;
	s << "You killed " << Name << ".";
	std::string Message(s.str());
	Game.ActionControl.QuickMessage(Message);

	int random = rand() % 100;
	int GiveItem;
	if (random <= 60 ) GiveItem = -1;
	if (random >= 61 || random <= 85) GiveItem = ITEM1;
	if (random >= 86 || random <= 95) GiveItem = ITEM2;
	if (random >= 96 || random <= 100) GiveItem = ITEM3;
	Game.Player1.GetStuff(EXP, GOLD, GiveItem, 1);
	
	//Call death animation, at the end of animation
	Dead = true; //This means it will be erased at the next call of OnLoop();

}
void CEnemy::MoveCheck() {
	if (LastMove + MOV_SPEED <= SDL_GetTicks()) {
		LastMove = SDL_GetTicks();
		srand ( time(NULL) );
		int MoveDirection = rand() % 4 + 1;
		if (MoveDirection == 1) {CEntity::OnMove(1, 0);}
		if (MoveDirection == 2) {CEntity::OnMove(0, 1);}
		if (MoveDirection == 3) {CEntity::OnMove(-1, 0);}
		if (MoveDirection == 4) {CEntity::OnMove(0, -1);}
	}
}