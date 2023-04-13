#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <assert.h>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <numeric>
#include <chrono>
#include <random>
#include <functional>
#include <tuple>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <array>
#include <bitset>
#include <unordered_map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;

//The renderer we'll be using
SDL_Renderer* gRenderer = NULL;

//Width and height of the screen
const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 650;

class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

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
};
