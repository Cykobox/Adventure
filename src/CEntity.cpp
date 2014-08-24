#include "CEntity.h"
#include "GFXMODE.h"

std::vector<CEntity*> CEntity::EntityList;
std::vector<CEntityCol> CEntityCol::EntityColList;

CEntityCol::CEntityCol() {
     EntityA = NULL;
     EntityB = NULL;
}


CEntity::CEntity() {
	 Entity_Texture = NULL;
     
     posX = 0;
     posY = 0;
     
     Width = 0;
     Height = 0;
     
     Anim_Bool = false;     //A bool switch to determine if the entity has an animation or not.. true = animated
     Trans_Bool = false;    //A bool switch to determine if the entity has a transparency or not... true = has transparency.
     
     Type = ENTITY_TYPE_GENERIC;   //What type of entity is it? Generic, Player, Enemy, NPC
     Dead = false;                 //Is the Entity dead?
}

CEntity::~CEntity() {
}

bool CEntity::OnLoad(SDL_Renderer *pRenderer, char* File, int Width, int Height, bool Animate, bool Transparency, int MaxFrames) {
	if (CRenderable::LoadTexture(pRenderer, File) == NULL) {
         return false;
     }

     Anim_Bool = Animate;
     Trans_Bool = Transparency;
     
	 /*  SETS TRANSPARENCY IN PICTURE.... NEEDS TO BE REPLACES IN NEW SDL2 System... 
     if (Trans_Bool == true) {
     CSurface::Transparent(Surf_Entity, 255, 0, 255);
     } */
     
     this->Width = Width;
     this->Height = Height;
     
     Anim_Control.MaxFrames = MaxFrames;
     
     return true;
}

void CEntity::OnLoop() {
     switch (GFXMODE::GFXMODE_Control.GET_GFX_MODE()) {
            case GFX_MODE_PC: {
                 if (Anim_Bool == true) {   //If the entity is flagged to animate... animate it.
                      OnAnimate();
                 } 
                 break;
            }     
            case GFX_MODE_8BIT: {
                 break;
            }
     }
}

void CEntity::OnRender(SDL_Renderer* pRenderer) {
     switch (GFXMODE::GFXMODE_Control.GET_GFX_MODE()) {
          case GFX_MODE_PC: {
			   SDL_Rect DesRect; // Destination Rect
			   SDL_Rect SrcRect; // Source Rect
			   SrcRect.h = TILE_SIZE;
			   SrcRect.w = TILE_SIZE;
			   SrcRect.x = 0;
			   SrcRect.y = 0;
			   DesRect.h = TILE_SIZE;
			   DesRect.w = TILE_SIZE;
			   DesRect.x = (posX - CCamera::CameraControl.GetX()) * TILE_SIZE;
			   DesRect.y = (posY - CCamera::CameraControl.GetY()) * TILE_SIZE;
			   CRenderable::RenderTextureToScreen(pRenderer, SrcRect, DesRect);
               break;
          }
          case GFX_MODE_8BIT: {
              /* 
			  if(Surf_Entity == NULL || Surf_Display == NULL) return;
     
               if(Anim_Bool == true){    //if the animation trigger is on, draw with the animations....
                    CSurface::OnDraw(Surf_Display, Surf_Entity, posX - CCamera::CameraControl.GetX(), posY - CCamera::CameraControl.GetY(), CurrentFrameCol * Width, (CurrentFrameRow + Anim_Control.GetCurrentFrame()) * Height, Width, Height);
               }
               if(Anim_Bool == false){   //if the animation trigger is off, then just draw it at given position
                    CSurface::OnDraw(Surf_Display, Surf_Entity, posX - CCamera::CameraControl.GetX(), posY - CCamera::CameraControl.GetY());
               }
			   */
               break;

          }
     }
}

void CEntity::OnCleanup() {
	if (Entity_Texture) {
		SDL_DestroyTexture(Entity_Texture);
     }
     
	Entity_Texture = NULL;
}
     
void CEntity::OnAnimate() {
    /* 
	if(MoveLeft) {
         CurrentFrameCol = 0;
     }else
     
     if(MoveRight) {
         CurrentFrameCol = 1;
     }
     
     Anim_Control.OnAnimate();
	*/

	//This was used in the animation controls but to simplify things
	//I removed the animation variables because nothing at this point is animated.
	//I'm keeping the code however just in case I want to reference it later.
}

void CEntity::OnCollision(CEntity * Entity) {
        //This is what happens when a collision is detected... right now its nothing.
}

void CEntity::OnMove(float MoveX, float MoveY) {
     switch (GFXMODE::GFXMODE_Control.GET_GFX_MODE()) {
            case GFX_MODE_PC: {
			//If GFX Mode = PC... do this shit...
                 if(PosValid((int)(posX + MoveX), (int)(posY + MoveY))== true) {
				 // If, Call "PosValid" Send it where you're trying to move and check to see if there is a collision, if not... proceed)
                      posX = posX + (int)MoveX;   //Apply the move
                      posY = posY + (int)MoveY;   //Apply the move
                      
					  if (Type == ENTITY_TYPE_PLAYER) {
							if ((posX - CCamera::CameraControl.GetX()) < 4) CCamera::CameraControl.X--;
							if ((posX - CCamera::CameraControl.GetX()) >11) CCamera::CameraControl.X++;
							if ((posY - CCamera::CameraControl.GetY()) < 4) CCamera::CameraControl.Y--;
							if ((posY - CCamera::CameraControl.GetY()) > 7) CCamera::CameraControl.Y++;
					  }
                      //If the character is getting close to the edge of the screen... move the camera... 
					  //NOTE!! This is disabled for entities that are not the character!!!
				 }
                 break;   
            }
            case GFX_MODE_8BIT: {
                 break;       
           }
     };
}

bool CEntity::PosValid(int NewX, int NewY) {
    bool Return = true;
    switch (GFXMODE::GFXMODE_Control.GET_GFX_MODE()) {
         case (GFX_MODE_PC): {
              //Entity to Entity collision
              if(Flags & ENTITY_FLAG_MAPONLY) {
              }else{
                  for(int i = 0;i < EntityList.size();i++) {
                      if(PosValidEntity(EntityList[i], NewX, NewY) == false) {
                          Return = false;
                      }
                  }
              }
              //Entity to Map Collision
              MTile* Tile = CArea::AreaControl.GetTile(NewX, NewY);
              if(PosValidTile(Tile) == false) {
                   Return = false;
              }
              
              break;
         }
              
         case (GFX_MODE_8BIT): {
		 }
         
		 default: {
         }
    }
    return Return;
}

bool CEntity::PosValidTile(MTile* Tile) {
     if(Tile == NULL) return true;
     
     if(Tile->TypeID == TILE_TYPE_BLOCK) return false;
     
     return true;
}

bool CEntity::PosValidEntity(CEntity* Entity, int NewX, int NewY) {
      if(this != Entity &&	// Don't check against ourself.
		  Entity != NULL && // don't check against NULL
		  Entity->Dead == false) {// don't check against Dead entities
		  //Entity->Flags ^ ENTITY_FLAG_MAPONLY && // don't check against??

		  if (Entity->posX == NewX && Entity->posY == NewY) { //Check for Collision
		//if the passed entity's position if the position of where the guy is trying to move...
                 //THERE IS A COLLISION!!
				CEntityCol EntityCol;
          
				EntityCol.EntityA = this;
				EntityCol.EntityB = Entity;
          
				CEntityCol::EntityColList.push_back(EntityCol);
          
				return false;
		  }
      }
      
      return true;
}











