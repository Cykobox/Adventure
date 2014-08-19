#include "CInventory.h"
#include "SInvItem.h"
#include "SItem.h"
#include "ADV.h"

CInventory::CInventory()
{

}

void CInventory::UseItem(int InvID, int ItemID, int EntityID) {
	
	// make sure it's a valid item.
	if( ItemID > -1 && ItemID < NUM_INV_ITEMS )
	{
		if( MasterItemList[ItemID].Use( MasterItemList[ItemID], EntityID ) )
		{
			Inventory[InvID].Number-- ;
			if (Inventory[InvID].Number == 0) {
				Inventory[InvID].ID = -1;
			}
		}
	}

}

void CInventory::AddItem(int ItemID, int Number) {

    bool found = false;
    int FirstEmpty = -1;
    
    for (int i = 0; i < 100 && found == false; i++) {
        if (Inventory[i].ID == ItemID) {
            Inventory[i].Number += Number;
            found = true;
        } else if(Inventory[i].ID == -1 && FirstEmpty == -1) {
            int FirstEmpty = i;
        } else {
            i++;
        }
    }
    
    if (found == false) {
        Inventory[FirstEmpty].ID = ItemID;
        Inventory[FirstEmpty].Number = Number;
    }
	Game.ActionControl.QuickMessage("A potion has been added to your inventory");
	
}
