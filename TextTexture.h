#pragma once
#include "LTexture.h"

using namespace std;


class TextTexture
{
public:
	//Initializes variables
	TextTexture();

	//Deallocates memory
	~TextTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, Uint8 r, Uint8 g, Uint8 b);

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

	// Set velocity
	void setVelocity(int vx, int vy);

	// Get velocity in x and y direction
	int getXVelocity();
	int getYVelocity();

	// Get position
	int getX();
	int getY();

	void move();

	void setPos(int x, int y);


private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;

	int mPosX, mPosY;
	int mVelX, mVelY;
};

TextTexture::TextTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mPosX = 0;
	mPosY = 0;
	mVelX = 0;
	mVelY = 0;
}

TextTexture::~TextTexture()
{
	//Deallocate
	free();
}

bool TextTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

bool TextTexture::loadFromRenderedText(std::string textureText, Uint8 r, Uint8 g, Uint8 b)
{
	//Get rid of preexisting texture
	free();

	//Color
	SDL_Color textColor{ r, g, b };

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mTexture != NULL;
}

void TextTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void TextTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void TextTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void TextTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void TextTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int TextTexture::getWidth()
{
	return mWidth;
}

int TextTexture::getHeight()
{
	return mHeight;
}

void TextTexture::setVelocity(int vx, int vy) {
	mVelX = vx;
	mVelY = vy;
}

int TextTexture::getX() {
	return mPosX;
}

int TextTexture::getY() {
	return mPosY;
}

void TextTexture::move() {
	mPosX += mVelX;
	mPosY += mVelY;

	// Gi?i h?n v? trí c?a TextTexture trong khu v?c c?a c?a s?
	if (mPosX < 0) {
		mVelX = -mVelX;
		//mPosX = 0;
	}
	else if (mPosX > SCREEN_WIDTH - mWidth) {
		mVelX = -mVelX;
		//mPosX = SCREEN_WIDTH - mWidth;
	}

	if (mPosY < 0) {
		mVelY = -mVelY;
		//mPosY = 0;
	}
	else if (mPosY > SCREEN_HEIGHT - mHeight) {
		mVelY = -mVelY;
		//mPosY = SCREEN_HEIGHT - mHeight;
	}
}

void TextTexture::setPos(int x, int y) {
	mPosX = x;
	mPosY = y;
}

int TextTexture::getXVelocity()
{
	return mVelX;
}

int TextTexture::getYVelocity()
{
	return mVelY;
}
