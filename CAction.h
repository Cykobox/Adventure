#ifndef _CACTION_H_
	#define _CACTION_H_

#include <list>
#include "CEntity.h"
#include <string>
#include "CMessage.h"

class CAction {		
	public:	
		CAction(int ActType, CEntity *SRC_Ent, int moveX, int moveY, bool PATC, bool LOCK, int DUR);				 //Move Action Constructor
		CAction(int ActType, CEntity* SRC_Ent, CEntity* TAR_Ent, bool PATC, bool LOCK, int DUR);					 //Attack Action Constructor
		CAction(int ActType, CEntity* SRC_Ent, std::string S_Mess, int iX, int iY, bool PATC, bool LOCK, int DUR);  //Message Action Constructor
		CAction();
	public:  //Shared Variables
		int Type;
		int X;
		int Y;
		CEntity *SRC_Entity;  //Entity that is the source of the action... NOTE: in movement actions, the SRC is the entity that moves.

	public:  //Variables for Attack Actions
		CEntity *TAR_Entity;  //Target Entity, the Entity that will be attacked


	public:  //Variables for Move Actions


	public:  //Variables for Message Actions
		std::string sMessage;   //Message to be displayed



	public:  //Variables for Flags and Locks
	/*flags and locks are things that determine how the game behaves while the game is executing each actions on the list
	ie, whether the game needs to block other actions, whether the action can be performed concurrently with other actions,
	whether an action requires the user to press A before it can move onto the next action... things like that*/
		bool fPATC;		//press a to continue flag
		bool fLOCK;		//lock all keyboard input
		int Duration;	//How long until the next Action can go, if zero, it can run concurrently with next
		
		
};


#endif