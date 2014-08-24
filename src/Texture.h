//
// Texture.h
// (c) Christopher Bauer 2014
//
// Responsibilities: Own a single texture and render it to the screen.
//

#include <string>
#include <SDL.h>

class Texture
{
public:
	Texture();
	~Texture();

	bool Load(SDL_Renderer* Renderer, std::string Filename);
	void Render(int X, int Y);
	void Render(int X, int Y, int Width, int Height);
	void Render(int X, int Y, int Width, int Height, int SX, int SY, int SWidth, int SHeight);
	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }

private:

	std::string mFilename;
	int mWidth = 0;
	int mHeight = 0;
	SDL_Renderer* mpRenderer = NULL;
	SDL_Texture* mpSDLTexture = NULL;

};