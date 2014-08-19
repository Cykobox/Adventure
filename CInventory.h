#ifndef _CINVENTORY_H_
        #define _CINVENTORY_H_

#include "SInvItem.h"
#include "CEntity.h"

class CInventory {
	public:
		InvItem Inventory[100];
             
        CInventory();
        void UseItem(int InvID, int ItemID, int EntityID);
        void AddItem(int ItemID, int Number);
};



#endif
