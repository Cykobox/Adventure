#include "CAction.h"
#include "GFXMODE.h"


CAction::CAction() {
	//default constructor... cause I can't get the other constructors to work right... they always say
	//"these parameters don't match the constructor's argument list"  ...which is crap. but whatever.
	Type = 3;
	X = 0, Y = 0;
	fPATC = false;
	fLOCK = false;
	Duration = 0;
	SRC_Entity = NULL;

}

CAction::CAction(int ActType, CEntity *SRC_Ent, int moveX, int moveY, bool PATC, bool LOCK, int DUR){  //Move Type Action
	Type = ActType;
	SRC_Entity = SRC_Ent;
	X = moveX;
	Y = moveY;
	fPATC = PATC;
	fLOCK = LOCK;
	Duration = DUR;
}

CAction::CAction(int ActType, CEntity* SRC_Ent, CEntity* TAR_Ent, bool PATC, bool LOCK, int DUR) {   //Attack Type Action
	Type = ActType;
	SRC_Entity = SRC_Ent;
	TAR_Entity = TAR_Ent;
	fPATC = PATC;
	fLOCK = LOCK;
	Duration = DUR;
}

CAction::CAction(int ActType, CEntity* SRC_Ent, std::string S_Mess, int iX, int iY, bool PATC, bool LOCK, int DUR) {  //Message Type Action
	Type = ActType;
	SRC_Entity = SRC_Ent;
	sMessage = S_Mess;
	X = iX;
	Y = iY;
	fPATC = PATC;
	fLOCK = LOCK;
	Duration = DUR;
}