#ifndef _SINVITEM_H_
        #define _SINVITEM_H_

// This struct is for an item held in the inventory.
// an array of these are used as the inventory for the player
// since the data for what each item IS is held in the Item struct
// this just needs a way to point to one of those for most of its data.
// all the inventory needs to know is what it is, and how many we're carrying.
struct InvItem {
	int ID;
	int Number;
};

#endif
