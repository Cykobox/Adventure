//
// Texture.cpp
// (c) Christopher Bauer 2014
//
// Responsibilities: Own a single texture and render it to the screen.
//

#include "Texture.h"
#include <SDL_image.h>

Texture::Texture()
	: mWidth(0)
	, mHeight(0)
	, mpRenderer( NULL )
	, mpSDLTexture( NULL )
{

}


Texture::~Texture()
{
	if( mpSDLTexture )
	{
		SDL_DestroyTexture(mpSDLTexture);
		mpSDLTexture = NULL;
	}
}


bool Texture::Load(SDL_Renderer* Renderer, std::string Filename)
{
	//*
	if (Renderer == NULL)
	{
		//Log("Bad SDL renderer passed");
		return false;
	}
	mpRenderer = Renderer;
	//this->mpRenderer = Filename;
	SDL_Surface* TempSurface = IMG_Load(Filename.c_str());
	if (TempSurface == NULL)
	{
		//Log("Unable to load image : %s : %s", Filename.c_str(), IMG_GetError());
		return false;
	}
	// Convert SDL surface to a texture
	if ((mpSDLTexture = SDL_CreateTextureFromSurface(Renderer, TempSurface)) == NULL)
	{
		//Log("Unable to create SDL Texture : %s : %s", Filename.c_str(), IMG_GetError());
		return false;
	}
	// Grab dimensions
	SDL_QueryTexture(mpSDLTexture, NULL, NULL, &mWidth, &mHeight);
	//Log("Texture Dimensions: %s : %d %d", Filename.c_str(), Width, Height);
	SDL_FreeSurface(TempSurface);
	return true;
	//*/
}

void Texture::Render(int X, int Y)
{
	Render(X, Y, mWidth, mHeight);
}

void Texture::Render(int X, int Y, int Width, int Height)
{
	SDL_Rect Destination = { X, Y, Width, Height };
	SDL_RenderCopy(mpRenderer, mpSDLTexture, NULL, &Destination);
}

void Texture::Render(int X, int Y, int Width, int Height, int SX, int SY, int SWidth, int SHeight)
{
	SDL_Rect Source = { SX, SY, SWidth, SHeight };
	SDL_Rect Destination = { X, Y, Width, Height };
	SDL_RenderCopy(mpRenderer, mpSDLTexture, &Source, &Destination);
}
