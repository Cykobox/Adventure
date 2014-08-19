#include "CActionListControl.h"
#include "CMessage.h"

ActionListControl::ActionListControl() {

}

void ActionListControl::OnLoad() {
	NextAct = 0;
	ActionList.clear();
	Press_A_To_Con = false;
	fLocked = false;
	Messages.AddMessage("Welcome to Adventure! w,a,s,d = Move, SpaceBar = Menu, Num Pad2 = Action", 0, 0, 0);
}

void ActionListControl::DoAction() {

	while ((ActionList.size() > 0) && 
		(Press_A_To_Con == false) && 
		(NextAct <= SDL_GetTicks())) {
		CAction tempAction = ActionList.front();        //Assign first action in list to temp action.	
			
		if (tempAction.Type == ACTION_TYPE_ATTACK) {     //If the action is an attack action...	
			
			AttackAction();								//call attack action function
			
			if (tempAction.fPATC == true) {				//CHeck Press A To Continue Flag
				Press_A_To_Con = true;
			}
			
			if (tempAction.fLOCK == true) {				//check fLock flag
				fLocked = true;
			}

			NextAct = (tempAction.Duration + SDL_GetTicks()); //make sure you lock the next action until this one is complete, 0 = concurrency
			ActionList.pop_front();						//Then kill the action
			LastAct = SDL_GetTicks();				//Log the time when it happened
				
		} else if (tempAction.Type == ACTION_TYPE_MOVE) {
			MoveAction();
			if (tempAction.fPATC == true) {				//CHeck Press A To Continue Flag
				Press_A_To_Con = true;
			}
			if (tempAction.fLOCK == true) {				//check fLock flag
				fLocked = true;
			}

			NextAct = (tempAction.Duration + SDL_GetTicks()); //make sure you lock the next action until this one is complete, 0 = concurrency
			ActionList.pop_front();						//Then kill the action
			LastAct = SDL_GetTicks();				//Log the time when it happened
				
		} else if (tempAction.Type == ACTION_TYPE_MESSAGE) {
			MessageAction();
			if (tempAction.fPATC == true) {				//CHeck Press A To Continue Flag
				Press_A_To_Con = true;
			}
			if (tempAction.fLOCK == true) {				//check fLock flag
				fLocked = true;
			}

			NextAct = (tempAction.Duration + SDL_GetTicks()); //make sure you lock the next action until this one is complete, 0 = concurrency
			ActionList.pop_front();						//Then kill the action
			LastAct = SDL_GetTicks();				//Log the time when it happened
				
		}

	}
}

void ActionListControl::AttackAction(){
	Messages.AddMessage("Attack Action: You attack the Enemy...", 0, 0, 0);

}
		
void ActionListControl::MoveAction(){
	CAction tempAction = ActionList.front();
	tempAction.SRC_Entity->OnMove(tempAction.X, tempAction.Y);
}

void ActionListControl::MessageAction(){
	CAction tempAction = ActionList.front();
	int n;
	char mess[128];
	n = sprintf(mess, "%s", tempAction.sMessage);
	Messages.AddMessage(mess, 0, 0, 0);
}

void ActionListControl::QuickMessage(std::string sMess){
	int n;
	char mess[128];
	n = sprintf(mess, "%s", sMess.c_str());
	Messages.AddMessage(mess, 0, 0, 0);
}

void ActionListControl::OnRenderMessage(SDL_Surface* Surf_Display){
    Messages.OnRender(Surf_Display);
}