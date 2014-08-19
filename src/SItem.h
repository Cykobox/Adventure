// Struct for item definitions.
// Everything that can go in the player's inventory (and some things that can't)
// has one of these structs to define what it does.
#ifndef __SITEM_H
#define __SITEM_H

// This should probably be a variable instead of a define.
#define NUM_INV_ITEMS 2

void InitializeItemList();

enum eItemType {
	eKeyItem,
	eEquipmentHead,
	eEquipmentChest,
	eEquipment1HWeapon,
	eEquipment2HWeapon,
	eUsable,
};


struct SItem
{
	int ID;				// identifying ID for this item.
	int stackLimit;		// How many of this item can be stacked in in one inventory slot.
	eItemType itemType;	// What kind of item is this?
	bool bUsable;		// Is this a usable item? (potions, or equipment that cast spells and the like)
	
	// data values do different things depending on what the item is.
	int data1;
	int data2;
	int data3;

	// "use" function for this item
	// Use functions take a single int that determins the target
	// Returns weather the item is consumed or not.
	bool (*Use)(SItem, int);
};

// Only 2 items so far, potion and HiPotion.
extern SItem MasterItemList[NUM_INV_ITEMS];

#endif