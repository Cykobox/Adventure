#include "CMenu.h"
#include "CText.h"
#include "CSurface.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>
#include "CPlayer.h"
#include "CTargeting.h"
#include "CEnemy.h"
#include "CEntity.h"

CMenu::CMenu() {
     Surf_Menu = NULL;
}

bool CMenu::OnLoad() { 
	
	if((Surf_Menu = CSurface::OnLoad("./images/menu-back.bmp")) == NULL ){
		return false;
	}

	//Initialize and Load CTexts... Don't forget this step...
	 Name.OnLoad("./fonts/PC-Font.ttf", 22);
     T_HP_LABEL.OnLoad("./fonts/PC-Font.ttf", 22);
     T_MP_LABEL.OnLoad("./fonts/PC-Font.ttf", 22);
     T_AP_LABEL.OnLoad("./fonts/PC-Font.ttf", 22);
	 T_TARGETING_MODE.OnLoad("./fonts/PC-Font.ttf", 22);
	 T_Tar_X.OnLoad("./fonts/PC-Font.ttf", 22);
	 T_Tar_Y.OnLoad("./fonts/PC-Font.ttf", 22);
	 T_PAUSE.OnLoad("./fonts/PC-Font.ttf", 22);
	 T_Facing.OnLoad("./fonts/PC-Font.ttf", 22);
	 
	 Name.X = 0;
     Name.Y = 0;

	 T_HP_LABEL.X = 5;
	 T_HP_LABEL.Y = 20;

	 T_MP_LABEL.X = 5;
	 T_MP_LABEL.Y = 40;

	 T_AP_LABEL.X = 5;
	 T_AP_LABEL.Y = 60;
	 
	 T_TARGETING_MODE.X = 5;
	 T_TARGETING_MODE.Y = 400;
	 
	 T_Tar_X.X = 5;
	 T_Tar_X.Y = 420;
	 
	 T_Tar_Y.X = 5;
	 T_Tar_Y.Y = 440;

	 T_Facing.X = 5;
	 T_Facing.Y = 460;
	 return true;
}

void CMenu::OnRender(CPlayer* Player1, SDL_Surface* Surf_Display, int X, int Y){
	 int n;

	 n = sprintf(T_HP_LABEL.Text, "HP: %d / %d", Player1->CUR_HP, Player1->MAX_HP);
	 n = sprintf(T_MP_LABEL.Text, "MP: %d / %d", Player1->CUR_MP, Player1->MAX_MP);
	 n = sprintf(T_AP_LABEL.Text, "AP: %d / %d", Player1->CUR_AP, Player1->MAX_AP);
	 if (Player1->TargetingSys.Targeting_Mode == true) {n = sprintf(T_TARGETING_MODE.Text, "Targeting Mode = True");}
	 if (Player1->TargetingSys.Targeting_Mode == false) {n = sprintf(T_TARGETING_MODE.Text, "Targeting Mode = False");}
	 n = sprintf(T_Facing.Text, "Character Facing = %d", Player1->Facing);
	 if (Player1->Target != NULL) {
		 n = sprintf(T_Tar_X.Text, "Tar X=%d, Y=%d", Player1->TargetingSys.Target->posX, Player1->TargetingSys.Target->posY);
		 n = sprintf(T_Tar_Y.Text, "Tar HP:%d/%d", Player1->TargetingSys.Target->Cur_HP, Player1->TargetingSys.Target->Max_HP);
	 }
	 else {
		 n = sprintf(T_Tar_X.Text, "Target X = , Target Y = ");
		 n = sprintf(T_Tar_Y.Text, "Target HP:   /  ");
	 }
	 n = sprintf(Name.Text, Player1->Char_Name);
	 
	 SDL_FillRect(Surf_Menu, NULL, 0x00000);
	 Name.OnRender(Surf_Menu);
	 T_HP_LABEL.OnRender(Surf_Menu);
	 T_MP_LABEL.OnRender(Surf_Menu);
	 T_AP_LABEL.OnRender(Surf_Menu);
	 T_TARGETING_MODE.OnRender(Surf_Menu);
	 T_Facing.OnRender(Surf_Menu);
	 T_Tar_X.OnRender(Surf_Menu);
	 T_Tar_Y.OnRender(Surf_Menu);
     CSurface::OnDraw(Surf_Display, Surf_Menu, X, Y);
}

void CMenu::OnCleanup(){
     SDL_FreeSurface(Surf_Menu);
     
	 Name.OnCleanup();
	 T_MP_LABEL.OnCleanup();
	 T_HP_LABEL.OnCleanup();
	 T_AP_LABEL.OnCleanup();


}
