#ifndef _ACTIONLISTCONTROL_H_
     #define _ACTIONLISTCONTROL_H_

#include "CAction.h"
#include "CMessage.h"
#include <list>

enum{
	ACTION_TYPE_ATTACK = 1,
	ACTION_TYPE_MOVE = 2,
	ACTION_TYPE_MESSAGE = 3,
};


class ActionListControl {
	public: 
		
		std::list<CAction> ActionList;

	public:
		int LastAct;		  //Ticks when the last action took place
		int NextAct;		  //Ticks when the next action goes off

		bool Press_A_To_Con;  //Press A to continue?
		bool fLocked;		  //Are Actions paused?

        CMessage    Messages;

		ActionListControl();

		void OnLoad();
		void DoAction();
		void AttackAction();
		void MoveAction();
		void MessageAction();
		void QuickMessage(std::string sMess);
		void OnRenderMessage(SDL_Surface* Surf_Display);


};

#endif
