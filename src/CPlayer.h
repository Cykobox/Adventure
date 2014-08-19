#ifndef _CPLAYER_H_
    #define _CPLAYER_H_

#include "CEntity.h"
#include "CTargeting.h"
#include "CEnemy.h"

enum eWeapon_Type {
	eOneHandedSword,
	eTwoHandedSword,
	eMace,
	eHammer,
	eKatana,
	eGun,
	eDagger,
	eBow,
	eStaff,
	eWand,
	eTomb,
	eRod,
	eCrossBow,
	eHandBomb,
	eSpear,
	ePole
};

class CPlayer : public CEntity {
    public:
        CPlayer();

        //Targeting Information
		CEnemy *Target;     //the entity that the current player is targeting
		int Facing;          //which direction is the player facing... 0 = up, 1 = right, 2 = down, 3 = left
		CTargeting	TargetingSys;

        char Char_Name[15]; //Character's name
        int MAX_HP;    //Hit points
        int CUR_HP;
        int MAX_MP;    //Magic Points
        int CUR_MP;
        int MAX_AP;    //Ability Points
        int CUR_AP;
        
        // THESE ARE THE STATUS VARIABLES... INCLUDING THEIR VALUES, GROWTH RATES AND EXPERIENCE
        
        int STR;   //Strength, physical attack
        int VIT;   //Vitality, physical Defense
        int DEX;   //Dexterity, speed
        int SPI;   //Spirit, magic attack
        int MAG;   //Mag, Magic Defense
        int LUC;   //Luck, how often critical hit, find items after battle
        
        long STREXP; //Strength Experience Points
        long VITEXP; //Vitality Experience Points
        long DEXEXP; //Dexterity Experience
        long SPIEXP; //Spirit Experience
        long MAGEXP; //Magic Experience
        long LUCEXP; //Luck Experience
        
        float STRGrowth;   //The growth rate of all the stats, these are effected by the equipment that character has equipped
        float VITGrowth;
        float DEXGrowth;
        float SPIGrowth;
        float MAGGrowth;
        float LUCGrowth;
        
        //THESE ARE THE ADJUSTED STATS, from which weapons and armor are equipped
        
        int ATT;             //Physical Attacks have a power and a percentage to hit
        int ATTPER;          //Physical Attack Percentage to hit
        int DEF;             //Defense Rating
        int DEFPER;          //Dodge Rate (Defense Percentage rate)
        int MAGPOW;          //Magic Attacks can't miss
        int MAGDEF;          //Magic Defense
        
        //THESE ARE THE SKILL AND WEAPON PROFICIENCIES... including their levels and rates
        
		//Proficiency LEVELS
        //Strength based weapons - Levels
        int OHS;   //1 handed sword - Can Equip Shield
        int THS;   //2 handed sword - Cannnot Equip Shield
        int MAC;   //Mace           - Can Equip Shield
        int HAM;   //Hammer         - Cannot Equip Shield
        
        //Dexterity and speed based weapons - Levels
        int KAT;   //Katana         - Cannot Equip Shield
        int GUN;   //Guns           - Cannot Equip Shield
        int DAG;   //Daggers        - Cannot Equip Shield
        int BOW;   //Bow            - Cannot Equip Shield
        
        //Magic Based Weapons - Levels
        int STA;    //Staffs, have a decent attack but also raise magick proficciencies.
        int WAN;    //Wands, low attack but higher learning rates - Can Equip Shield
        int TOM;    //Tombs, have no attack power but have really high learning rates
        int ROD;    //Rods, also contain a boost effect, when you hit somebody with it it adds protect = medium learning rates
        
        //Hybrid Weapons - Levels
        int CRO;   //Cross bow   STR and DEX - Long Range
        int BOM;   //HANDBOMBS   DEX and MAG - Can Equip Shield - Long Range
        int SPE;   //Spear       STR and DEX
        int POL;   //Pole        STR and MAG
        
		//Proficiencies RATES OF GROWTH
		//Strength based weapons - RATES OF GROWTH
        int OHS_RATE;   //1 handed sword - Can Equip Shield
        int THS_RATE;   //2 handed sword - Cannnot Equip Shield
        int MAC_RATE;   //Mace           - Can Equip Shield
        int HAM_RATE;   //Hammer         - Cannot Equip Shield
        
        //Dexterity and speed based weapons - RATE OF GROWTH
        int KAT_RATE;   //Katana         - Cannot Equip Shield
        int GUN_RATE;   //Guns           - Cannot Equip Shield
        int DAG_RATE;   //Daggers        - Cannot Equip Shield
        int BOW_RATE;   //Bow            - Cannot Equip Shield
        
        //Magic Based Weapons - RATE OF GROWTH
        int STA_RATE;    //Staffs, have a decent attack but also raise magick proficciencies.
        int WAN_RATE;    //Wands, low attack but higher learning rates - Can Equip Shield
        int TOM_RATE;    //Tombs, have no attack power but have really high learning rates
        int ROD_RATE;    //Rods, also contain a boost effect, when you hit somebody with it it adds protect = medium learning rates
        
        //Hybrid Weapons - RATE OF GROWTH
        int CRO_RATE;   //Cross bow   STR and DEX - Long Range
        int BOM_RATE;   //HANDBOMBS   DEX and MAG - Can Equip Shield - Long Range
        int SPE_RATE;   //Spear       STR and DEX
        int POL_RATE;   //Pole        STR and MAG

        int Weapon_ID;      //ID of Weapon Equipped
        eWeapon_Type Weapon_Type;	//Type of Weapon Equipped -- to determine which attack equasion to use.
		int Armor_ID;       //ID of Armor Equipped
        int Shield_ID;      //ID of Shield Equipped
        int Helm_ID;        //ID of Helm Equipped
        int Accessory1_ID;  //ID of First Accessory Equipped
        int Accessory2_ID;  //ID of Second Accessory Equipped
		int Bank;			//How much money's the playa haz.
        
        void HPCheck();     //See if the character is dead...
        void Attack(CEnemy *Tar_Enemy);
		void GetStuff(int GetEXP, int GetGold, int GetItemID, int GetItemNum);

        void FindTarget();
		void FindPrevTarget();
		void FindNextTarget();
		void LockTarget();

        bool OnLoad(char* File, int Width, int Height, bool Animate, bool Transparency, int MaxFrames);
        void OnMove(float MoveX, float MoveY);
        void OnLoop();
        void OnRender(SDL_Surface* Surf_Display);
        void OnCleanup();
        void OnAnimate();
        void OnCollision(CEntity* Entity);
};
 
#endif          
