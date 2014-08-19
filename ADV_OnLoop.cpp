#include "ADV.h"
#include <vector>

void AdvGame::OnLoop() {
     
     CFPS::FPSControl.OnLoop();
     
	 std::vector<CEntity*>::iterator it = CEntity::EntityList.begin();

     for(int i = 0; i < CEntity::EntityList.size(); i++){
             if(!CEntity::EntityList[i]) continue;
			 if (CEntity::EntityList[i]->Dead == true) {
				 CEntity::EntityList.erase(it);
			 } else {
				CEntity::EntityList[i]->OnLoop();
			 }
			 it++;
     }

	 ActionControl.DoAction();
     
}
