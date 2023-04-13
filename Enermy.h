#pragma once
#include "LTexture.h"

class Enermy
{
public:
	//Initializes variables
	Enermy();

	//Deallocates memory
	~Enermy();

	//Loads image at specified path
	bool loadFromFile(std::string path);

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

	bool renew_flag;
};

Enermy::Enermy()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mPosX = 0;
	mPosY = 0;
	mVelX = 0;
	mVelY = 0;
	renew_flag = false;
}

Enermy::~Enermy()
{
	//Deallocate
	free();
}

bool Enermy::loadFromFile(std::string path)
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

void Enermy::free()
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

void Enermy::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void Enermy::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void Enermy::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void Enermy::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
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

int Enermy::getWidth()
{
	return mWidth;
}

int Enermy::getHeight()
{
	return mHeight;
}

void Enermy::setVelocity(int vx, int vy) {
	mVelX = vx;
	mVelY = vy;
}

int Enermy::getX() {
	return mPosX;
}

int Enermy::getY() {
	return mPosY;
}

void Enermy::move() {
	mPosX += mVelX;
	mPosY += mVelY;

	//cout << "PosY: " << mPosY << " SCREEN_HEIGHT: " <<  SCREEN_HEIGHT << endl;

	if (mPosY > SCREEN_HEIGHT)
	{
		renew_flag = true;
	}

	if (renew_flag)
	{
		renew_flag = false;
		mPosX = rand() % (SCREEN_WIDTH - mWidth);
		mPosY = -mHeight - 50;
	}

	/*
	// Giới hạn vị trí của Enermy trong khu vực của cửa sổ
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
	*/
}

void Enermy::setPos(int x, int y) {
	mPosX = x;
	mPosY = y;
}

int Enermy::getXVelocity()
{
	return mVelX;
}

int Enermy::getYVelocity()
{
	return mVelY;
}
