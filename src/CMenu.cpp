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
#include <iostream>

CMenu::CMenu() {
	My_Texture = NULL;
}

bool CMenu::OnLoad(SDL_Renderer *pRenderer, int height, int width, int x, int y) {
	Menu_Width = width;
	Menu_Height = height;
	Menu_X = x;
	Menu_Y = y;

	My_Texture = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Menu_Width, Menu_Width);
	if(LoadTexture(pRenderer, ("./images/menu-back.bmp")) == false){
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

void CMenu::OnRender(CPlayer* Player1, SDL_Renderer* pRenderer){
	 sprintf_s(T_HP_LABEL.Text, _countof(T_HP_LABEL.Text), "HP: %d / %d", Player1->CUR_HP, Player1->MAX_HP);
	 sprintf_s(T_MP_LABEL.Text, _countof(T_MP_LABEL.Text), "MP: %d / %d", Player1->CUR_MP, Player1->MAX_MP);
	 sprintf_s(T_AP_LABEL.Text, _countof(T_AP_LABEL.Text), "AP: %d / %d", Player1->CUR_AP, Player1->MAX_AP);
	 if (Player1->TargetingSys.Targeting_Mode == true)
	 {
		 sprintf_s(T_TARGETING_MODE.Text, _countof(T_TARGETING_MODE.Text), "Targeting Mode = True");
	 }
	 else
	 {
		 sprintf_s(T_TARGETING_MODE.Text, _countof(T_TARGETING_MODE.Text), "Targeting Mode = False");
	 }

	 sprintf_s(T_Facing.Text, _countof(T_Facing.Text), "Character Facing = %d", Player1->Facing);

	 if (Player1->Target != NULL)
	 {
		 sprintf_s(T_Tar_X.Text, _countof(T_Tar_X.Text), "Tar X=%d, Y=%d", Player1->TargetingSys.Target->posX, Player1->TargetingSys.Target->posY);
		 sprintf_s(T_Tar_Y.Text, _countof(T_Tar_Y.Text), "Tar HP:%d/%d", Player1->TargetingSys.Target->Cur_HP, Player1->TargetingSys.Target->Max_HP);
	 }
	 else
	 {
		 sprintf_s(T_Tar_X.Text, _countof(T_Tar_X.Text), "Target X = , Target Y = ");
		 sprintf_s(T_Tar_Y.Text, _countof(T_Tar_Y.Text), "Target HP:   /  ");
	 }
	 sprintf_s(Name.Text, _countof(Name.Text), Player1->Char_Name);
	 
	 LoadTexture(pRenderer, ("./images/menu-back.bmp")); //makes the background of the menu grey, aka, loads the menu background
	 
	 //std::cout << "After Load Texture\n";
	 
	 SDL_SetRenderTarget(pRenderer, My_Texture); //Set our renderer to render all things to our My_Texture texture and not to screen... so keep the menu on one texture
	 
	 
	 Name.OnRender(pRenderer);
	 T_HP_LABEL.OnRender(pRenderer);
	 T_MP_LABEL.OnRender(pRenderer);
	 T_AP_LABEL.OnRender(pRenderer);
	 T_TARGETING_MODE.OnRender(pRenderer);
	 T_Facing.OnRender(pRenderer);
	 T_Tar_X.OnRender(pRenderer);
	 T_Tar_Y.OnRender(pRenderer);
	 
	 SDL_Rect DESRect;

	 DESRect.h = Menu_Height;
	 DESRect.w = Menu_Width;
	 DESRect.x = Menu_X;
	 DESRect.y = Menu_Y;

	 SDL_SetRenderTarget(pRenderer, NULL);  // Set the place to render back to NULL, meaning "The Screen"
	 SDL_RenderCopy(pRenderer, My_Texture, NULL, &DESRect); //Renders our My_Texture, with our menu drawn on it... to the screen.
}

void CMenu::OnCleanup(){
     bool whocares = DestroyTextures();
     
	 Name.OnCleanup();
	 T_MP_LABEL.OnCleanup();
	 T_HP_LABEL.OnCleanup();
	 T_AP_LABEL.OnCleanup();


}
