#include "ADV.h"

void AdvGame::OnEvent(SDL_Event* Event) {
     CEvent::OnEvent(Event);
}

void AdvGame::OnExit() {
     Running = false;     
}

void AdvGame::OnKeyDown(SDL_Keysym sym) {
	/*
	switch (GFXMODE::GFXMODE_Control.GET_GFX_MODE()) {
          case (GFX_MODE_PC): {
               switch (sym) {
                    case SDLK_w: {								//move up
						Player1.OnMove(0, -1);  
						//CAction tempAction(1, Player1, 0, -1, false, false, 0); 
						//ActionControl.ActionList.push_back(tempAction);
						break;
						}
                    case SDLK_s: {								//move down
						Player1.OnMove(0, 1); 
						//CAction tempAction(1, Player1, 0, 1, false, false, 0); 
						//ActionControl.ActionList.push_back(tempAction);
						break;  
						}
                    case SDLK_a: {								//move left
						Player1.OnMove(-1, 0);
						//CAction tempAction(1, Player1, -1, 0, false, false, 0); 
						//ActionControl.ActionList.push_back(tempAction);
						break; 
						}
                    case SDLK_d: {								//move right
						Player1.OnMove(1, 0);
						//CAction tempAction(1, Player1, 1, 0, false, false, 0); 
						//ActionControl.ActionList.push_back(tempAction);
						break;  
						}
					case SDLK_g: Player1.CUR_HP = Player1.CUR_HP - 10; break;
					case SDLK_SPACE: {
                         if (Menu_Vis) {
                              Menu_Vis = false;
                         }else{ Menu_Vis = true;}
                         break;
                    }
                    case SDLK_ESCAPE: Running = false; break;
                    case SDLK_z: ActionControl.Messages.AddMessage("Adventure!", 0, 0, 0); break;
                    case SDLK_x: ActionControl.Messages.AddMessage("The Best Game Ever!!", 0, 0, 0); break;
                    case SDLK_c: ActionControl.Messages.AddMessage("Once I finish it, that is...", 0, 0, 0); break;
                    case SDLK_v: ActionControl.Messages.AddMessage("Written and coded by, Timothy Bauer", 0, 0, 0); break;
                    case SDLK_b: ActionControl.Messages.AddMessage("And don't forget the graphics too...", 0, 0, 0); break;
					case SDLK_h: InventoryManager.AddItem(0, 1); break;  //Add a Potion to the inventory (Potion ID is 0)
					case SDLK_j: InventoryManager.UseItem(0, 0, 1); break; //use a potion from the inventory (Potion ID is 0)
					case SDLK_KP4:{
						if ((Player1.TargetingSys.Targeting_Mode == true) || (Pause == false) || (ActionControl.Press_A_To_Con == false)) {
							Player1.FindPrevTarget();
						}
						break;
					case SDLK_KP6:{
						if ((Pause == true) || (ActionControl.Press_A_To_Con == true)) {//If either Paused or PATC... do nothing.
							break;
						}else if (Player1.TargetingSys.Targeting_Mode == true) {
							Player1.FindNextTarget();	
							break;														//If already in targeting mode... find Next Target
						}else if (Player1.TargetingSys.Targeting_Mode == false) {
							Player1.TargetingSys.Targeting_Mode = true;					//If Not in Targeting mode... go into targeting mode
							Player1.FindTarget();
							break;
						}
					}
					case SDLK_KP2:{  //action button. At some point this needs to be moved so that any key can be assigned as the action button.
						
						if (Pause == true) {
							break;
						} else if (ActionControl.Press_A_To_Con == true) {
							ActionControl.Press_A_To_Con = false;
							break;
						} else if (Player1.TargetingSys.Targeting_Mode == true){
							Player1.LockTarget();
							Player1.TargetingSys.Targeting_Mode = false;
							break;
						} else if (Player1.Target->Type == ENTITY_TYPE_ENEMY){
							Player1.Attack(Player1.Target);
							break;
						} else if (Player1.Target->Type == NULL) {
						    //figure out if there is an entity in front of the player, then figure out its type
							//and do what needs to be done
							//if NPC, then call player1.talk()
							//If chest, then call Chest.Openthatshits
							//if nothing, then search the ground.
							break;
						}	
					}; break;
                    default: {
					}
               break;
               }
          }
          case (GFX_MODE_8BIT): {
               
               switch(sym) {
          
                    case SDLK_LEFT: {
              
                         break;
                    }
          
                    case SDLK_RIGHT: {
                         
                         break;
                    }
          
                    default: {
                    }
               break;
          }
          default:{
          }
          }
		}
	}
	*/
}

void AdvGame::OnKeyUp(SDL_Keysym sym) {
	/*
     switch(sym) {
         case SDLK_LEFT: {
            if ((Player1.TargetingSys.Targeting_Mode == true) || (Pause == false) || (ActionControl.Press_A_To_Con == false)) {
				Player1.FindPrevTarget();
			}
			break;
         }
         case SDLK_RIGHT: {
            if ((Player1.TargetingSys.Targeting_Mode == true) || (Pause == false) || (ActionControl.Press_A_To_Con == false)) {
				Player1.FindNextTarget();
			}
			break;
         }
         default: {
         break;
         }
     }
	 */
}
