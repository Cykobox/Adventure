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
	void Render(int X, int Y) const;
	void Render(int X, int Y, int Width, int Height) const;
	void Render(int X, int Y, int Width, int Height, int SX, int SY, int SWidth, int SHeight) const;
	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }

private:

	std::string mFilename;
	int mWidth = 0;
	int mHeight = 0;
	SDL_Renderer* mpRenderer = NULL;
	SDL_Texture* mpSDLTexture = NULL;

};