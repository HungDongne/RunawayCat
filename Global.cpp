#include "Global.h"

using namespace std;

//The renderer we'll be using
SDL_Renderer* gRenderer = NULL;

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

//Globally used font
TTF_Font* gFont = NULL;

SDL_Surface* icon = NULL;

SDL_Cursor* cursor = NULL;

LTexture cat;
LTexture mouse_computer;
LTexture cat_cry;
LTexture game_over_image;
LTexture background;
LTexture Font;
Enermy dog;
Food pate;

int Score = 0;
int armo = 0; 
int Push_Count = 0;
Uint32 startTime = SDL_GetTicks();
