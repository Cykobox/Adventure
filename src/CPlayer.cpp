#include "CPlayer.h"
#include <math.h>
#include "ADV.h"
#include <string>
#include <sstream>

CPlayer::CPlayer() {
	Type = ENTITY_TYPE_PLAYER;
	Facing = 0;
}

bool CPlayer::OnLoad(char* File, int Width, int Height, bool Animate, bool Transparency, int MaxFrames) {
     if (CEntity::OnLoad(File, Width, Height, Animate, Transparency, MaxFrames) == false) {
          return false;
     }
     TargetingSys.OnLoad("./images/pc_Target.bmp", "./images/pc_PossTarget.bmp");
	 TargetingSys.Targeting_Mode = false;

	 MAX_HP = sprintf(Char_Name, "Enix");
	 MAX_HP = 370;
	 CUR_HP = 200;
	 MAX_MP = 10;
	 CUR_MP = 0;
	 MAX_AP = 3;
	 CUR_AP = 0;
	 Weapon_Type = eOneHandedSword;
	 OHS = 10;
	 STR = 10;
	 ATT = 10;
     return true;
}

void CPlayer::OnLoop() {
     CEntity::OnLoop();
}

void CPlayer::OnMove(float MoveX, float MoveY) {
	if (MoveX == -1) {Facing = 3;}
	if (MoveX == 1) {Facing = 1;}
	if (MoveY == -1) {Facing = 0;}
	if (MoveY == 1) {Facing = 2;}
	CEntity::OnMove(MoveX, MoveY);
}

void CPlayer::OnRender(SDL_Surface* Surf_Display) {
     CEntity::OnRender(Surf_Display);
	 TargetingSys.OnRender(Surf_Display);
}

void CPlayer::OnCleanup(){
     CEntity::OnCleanup();
	 TargetingSys.OnCleanup();
}

void CPlayer::OnAnimate() {
     CEntity::OnAnimate();     
}

void CPlayer::OnCollision(CEntity* Entity) {
}

void CPlayer::HPCheck() {
     if (CUR_HP > MAX_HP) CUR_HP = MAX_HP;
     if (CUR_HP < 1 ) {
         CUR_HP = 0;
         //Call death function
     }
}

void CPlayer::Attack(CEnemy *Tar_Enemy) {
	
	//find range
	int range;  //actually range squared... to prevent having to use the square root function
	range = ((Tar_Enemy->posX - posX) * (Tar_Enemy->posX - posX)) + ((Tar_Enemy->posY - posY) * (Tar_Enemy->posY - posY));

	//call swing animation... at some point this will exist
	switch(Weapon_Type) {
		case eOneHandedSword:{
			if (range < 3) {
				double random; 
				random = rand() % 255;
				//figure out if the player hits or not
				if (random + (DEX / 4) + ATTPER >= Tar_Enemy->DEFPercent) {
					double basedamage;
					double finaldamage;
					
					random = rand() % 25;
					random = (double)random / 100 + 1;		//create a number between 1 and 1.25
					
					basedamage = ((double)OHS / 2.5) * (STR + ((double)ATT * random) - Tar_Enemy->DEF);  //works
					finaldamage = basedamage - (basedamage * ((double)Tar_Enemy->DEF / 128));				//works
					
					//Base Damage= (SKILL/2.5) * (STAT + (Weapon Attack Power * Rand(1-1.25)) - DEF)
					//Damage = Base Damage - (Base Damage * (DEF / 128))
					int damage = (int)(finaldamage);
					if (damage < 0) damage = 0;
					Tar_Enemy->Cur_HP = Tar_Enemy->Cur_HP - damage;
					
					//Message Block////////////////////////////////////////////////
					std::ostringstream s;
					s << "You Hit Target for " << damage << " Damage.";
					std::string Message(s.str());
					Game.ActionControl.QuickMessage(Message);
					//End Message block///////////////////////////
					
					Tar_Enemy->HPCheck();
				}else {
					Game.ActionControl.QuickMessage("You Missed!");
				}
			} else {
				Game.ActionControl.QuickMessage("Target is Out of Range");
			}
			break;
		}
		case eTwoHandedSword:{
			if (range < 3) {
				double random; 
				random = rand() % 255;
				//figure out if the player hits or not
				if (random + (DEX / 4) + ATTPER >= Tar_Enemy->DEFPercent) {
					int basedamage;
					int damage;
					random = rand() % 25;
					random = (double)random / 100 + 1;		//create a number between 1 and 1.25
					basedamage = (THS / 2) * (STR + (ATT * random) - Tar_Enemy->DEF);
					damage = basedamage - (basedamage * (Tar_Enemy->DEF / 128));
					//Base Damage = (SKILL/2) * (STAT + (Weapon Attack Power * Rand(1-1.25)) - DEF)
					//Final Damage = Base Damage - (Base Damage * (DEF / 128))
					if (damage < 0) damage = 0;
					Tar_Enemy->Cur_HP = Tar_Enemy->Cur_HP - damage;
					Game.ActionControl.QuickMessage("You Attacked Target... You did ?? damage... sorry.");
				}else {
					Game.ActionControl.QuickMessage("You Missed!");
				}
			} else {
				Game.ActionControl.QuickMessage("Enemy is Out of Range");
			}
			break;
		}
		case eMace:{
			if (range < 3) {
				double random; 
				random = rand() % 255;
				//figure out if the player hits or not
				if (random + (DEX / 4) + ATTPER >= Tar_Enemy->DEFPercent) {
					int basedamage;
					int damage;
					random = rand() % 25;
					random = (double)random / 100 + 1;				//create a number between 1 and 1.25
					basedamage = (MAC / 2.5) * (STR + (ATT * random) - Tar_Enemy->DEF);
					damage = basedamage - (basedamage * (Tar_Enemy->DEF / 128));
					//Base Damage = (SKILL/2.5) * (STAT + (Weapon Attack Power * Rand(1-1.25)) - DEF)
					//Final Damage = Base Damage - (Base Damage * (DEF / 128))
					if (damage < 0) damage = 0;
					Tar_Enemy->Cur_HP = Tar_Enemy->Cur_HP - damage;
					Game.ActionControl.QuickMessage("You Attacked Target... You did ?? damage... sorry.");
				}else {
					Game.ActionControl.QuickMessage("You Missed!");
				}
			} else {
				Game.ActionControl.QuickMessage("Enemy is Out of Range");
			}
			break;
		}
		case eHammer:{
			if (range < 3) {
				double random; 
				random = rand() % 255;
				//figure out if the player hits or not
				if (random + (DEX / 4) + ATTPER >= Tar_Enemy->DEFPercent) {
					int basedamage;
					int damage;
					random = rand() % 75 + 75;
					random = (double)random / 100 + 1; 		//create a number between .75 and 1.5
					basedamage = (HAM / 2) * (STR + (ATT * random) - Tar_Enemy->DEF);
					damage = basedamage - (basedamage * (Tar_Enemy->DEF / 128));
					//Base Damage = (SKILL/2) * (STAT + (Weapon Attack Power * Rand(.75-1.5)) - DEF)
					//Final Damage = Base Damage - (Base Damage * (DEF / 128))
					Tar_Enemy->Cur_HP = Tar_Enemy->Cur_HP - damage;
					Game.ActionControl.QuickMessage("You Attacked Target... You did ?? damage... sorry.");
				}else {
					Game.ActionControl.QuickMessage("You Missed!");
				}
			} else {
				Game.ActionControl.QuickMessage("Enemy is Out of Range");
			}
			break;
		}
		case eKatana:{
			if (range < 3) {
				double random; 
				random = rand() % 255;
				//figure out if the player hits or not
				if (random + (DEX / 4) + ATTPER >= Tar_Enemy->DEFPercent) {
					int basedamage;
					int damage;
					random = rand() % 25;					
					random = (double)random / 100 + 1;		//create a number between 1 and 1.25
					basedamage = (KAT / 2) * (DEX + (ATT * random) - Tar_Enemy->DEF);
					damage = basedamage - (basedamage * (Tar_Enemy->DEF / 128));
					//Base Damage = (SKILL/2) * (STAT + (Weapon Attack Power * Rand(1-1.25)) - DEF)
					//Final Damage = Base Damage - (Base Damage * (DEF / 128))
					if (damage < 0) damage = 0;
					Tar_Enemy->Cur_HP = Tar_Enemy->Cur_HP - damage;
					Game.ActionControl.QuickMessage("You Attacked Target... You did ?? damage... sorry.");
				}else {
					Game.ActionControl.QuickMessage("You Missed!");
				}
			} else {
				Game.ActionControl.QuickMessage("Enemy is Out of Range");
			}
			break;
		}
		case eGun:{
			Game.ActionControl.QuickMessage("Not Implimented yet... wait... how did you get this weapon anyways?");
			break;
		}
		case eDagger:{
			Game.ActionControl.QuickMessage("Not Implimented yet... wait... how did you get this weapon anyways?");
			break;
		}
		case eBow:{
			Game.ActionControl.QuickMessage("Not Implimented yet... wait... how did you get this weapon anyways?");
			break;
		}
		case eStaff:{
			Game.ActionControl.QuickMessage("Not Implimented yet... wait... how did you get this weapon anyways?");
			break;
		}
		case eWand:{
			Game.ActionControl.QuickMessage("Not Implimented yet... wait... how did you get this weapon anyways?");
			break;
		}
		case eTomb:{
			Game.ActionControl.QuickMessage("Not Implimented yet... wait... how did you get this weapon anyways?");
			break;
		}
		case eRod:{
			Game.ActionControl.QuickMessage("Not Implimented yet... wait... how did you get this weapon anyways?");
			break;
		}
		case eCrossBow:{
			Game.ActionControl.QuickMessage("Not Implimented yet... wait... how did you get this weapon anyways?");
			break;
		}
		case eHandBomb:{
			Game.ActionControl.QuickMessage("Not Implimented yet... wait... how did you get this weapon anyways?");
			break;
		}
		case eSpear:{
			Game.ActionControl.QuickMessage("Not Implimented yet... wait... how did you get this weapon anyways?");
			break;
		}
		case ePole:{
			Game.ActionControl.QuickMessage("Not Implimented yet... wait... how did you get this weapon anyways?");
			break;
		}
		default: {
			break;
		}
	}
}

void CPlayer::FindTarget() {
	//This is what needs to be done... and then it SHOULD work...
	////////////////////////////////////////////////////////////////
	double x1, x2, y1, y2, dist_square;
	int poss_tar_id = 0;			 //Possible target ID...
	double poss_tar_dist = 170;   //posible target max Distance
	x1 = posX;  //players x position
	y1 = posY;  //players y position

	for (int i = 0; i < CEntity::EntityList.size(); i++) {
		if (CEntity::EntityList[i]->Type == ENTITY_TYPE_ENEMY) {
			x2 = CEntity::EntityList[i]->posX;
			y2 = CEntity::EntityList[i]->posY;
			dist_square = (  pow((x2 - x1), 2)  +  pow((y2 - y1), 2) );  // Calculate the distance from Player to Entity
			if (dist_square < poss_tar_dist) {    //if the checked target is closer than the previous closest...
				poss_tar_id = i;
				poss_tar_dist = dist_square;      //make just checked
			}  //end of 2nd if statement
		} //end of 1st if statement
	} //end of for loop
	// old line:
	//TargetingSys.Target = CEnemy.EntityList[poss_tar_id];  //This Dont Work  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// Working line:
	// (CEnemy*) is called a 'cast'. It changes the pointer from a CEntity* to a CEnemy*.
	// Normally this is dangerous, but since we know that it's a CEnemy in this position (due to the if Type == ENTITY_TYPE_ENEMY above)
	// this lets us pull the CEnemy pointer back out of the list of CEntities.
	TargetingSys.Target = (CEnemy*)CEntity::EntityList[poss_tar_id];
}

void CPlayer::GetStuff(int GetEXP, int GetGold, int GetItemID, int GetItemNum){
	if (GetEXP > 0) {
		//give EXP to everything that needs it.
		std::ostringstream s;
		s << "You Recieved " << GetEXP << " Experience.";
		std::string Message(s.str());
		Game.ActionControl.QuickMessage(Message);
		//Check Levels
	}
	if (GetGold > 0) {
		Bank += GetGold;
		std::ostringstream s;
		s << "You Recieved " << GetGold << " Gold.";
		std::string Message(s.str());
		Game.ActionControl.QuickMessage(Message);
	}
	if (GetItemID > -1) {
		Game.InventoryManager.AddItem(GetItemID, GetItemNum);
	}


}

void CPlayer::FindPrevTarget(){
	FindTarget();
}

void CPlayer::FindNextTarget() {
	FindTarget();
}

void CPlayer::LockTarget() {
	Target = TargetingSys.Target;
}