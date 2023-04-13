#ifndef GLOBAL_H
#define GLOBAL_H

#include "Lib.h"
#include "LTexture.h"
#include "Enermy.h"
#include "Food.h"

using namespace std;

//The renderer we'll be using
extern SDL_Renderer* gRenderer;

// The window we'll be rendering to
extern SDL_Window* gWindow;

//Globally used font
extern TTF_Font* gFont;

extern SDL_Surface* icon;

extern SDL_Cursor* cursor;

extern LTexture cat;
extern LTexture mouse_computer;
extern LTexture cat_cry;
extern LTexture game_over_image;
extern LTexture background;
extern LTexture Font;
extern Enermy dog;
extern Food pate;
extern int Score;
extern int armo;
extern int Push_Count;
extern Uint32 startTime;


#endif // !GLOBAL_H
