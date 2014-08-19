#include "SItem.h"
#include "ADV.h"

///////////////////////////////////////////////////////////////////////////////
//  Item Use functions.
//
//  Each of these needs to have the signature:
//  int function_name( int );
//
///////////////////////////////////////////////////////////////////////////////
SItem MasterItemList[NUM_INV_ITEMS];

// simple health restoration item
bool restoreHealth( SItem whichItem, int target )
{
	// 	restore player health equal to whichItem.data1;
	Game.Player1.CUR_HP += whichItem.data1;
	if (Game.Player1.CUR_HP > Game.Player1.MAX_HP )
	{
		Game.Player1.CUR_HP = Game.Player1.MAX_HP;
	}
	Game.ActionControl.QuickMessage("You used a potion");
	return 1;
}

// Function for any item that can be used to cast a spell
bool CastSpell( SItem whichItem, int target )
{
	return 0;
}

void InitializeItemList()
{
	// Optiamally, we'd read the data from a file here, so we don't have to recompile every time we change an item

	// Healing Item - Potion.
	MasterItemList[0].ID = 0;
	MasterItemList[0].stackLimit = 99;
	MasterItemList[0].itemType = eUsable;
	MasterItemList[0].bUsable = true;
	MasterItemList[0].data1 = 40; 
	MasterItemList[0].data2 = 0;
	MasterItemList[0].data3 = 0;
	MasterItemList[0].Use = restoreHealth;

	// Healing Item High Potion
	MasterItemList[1].ID = 1;
	MasterItemList[1].stackLimit = 99;
	MasterItemList[1].itemType = eUsable;
	MasterItemList[1].bUsable = true;
	MasterItemList[1].data1 = 80; 
	MasterItemList[1].data2 = 0;
	MasterItemList[1].data3 = 0;
	MasterItemList[1].Use = restoreHealth;

}