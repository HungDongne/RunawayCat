#ifndef GLOBAL_H
#define GLOBAL_H

#include "Lib.h"
#include "LTexture.h"
#include "Enermy.h"
#include "Food.h"
#include "LTimer.h"

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
extern LTexture game_over_image;
extern LTexture background;
extern LTexture Font;
extern Enermy dog;
extern Enermy dog2;
extern Food pate;

extern bool GAME_OVER;

extern int Score;
extern int armo;
extern int Push_Count;
extern stringstream cout_score;
extern Uint32 startTime;
extern float avgFPS;
extern float angle_arrow;
extern LTexture gFPSTextTexture;
extern LTexture Arrow;

extern Mix_Music* Music_sound;
extern Mix_Chunk* Fire_sound;
extern Mix_Chunk* Lose_sound;
extern Mix_Chunk* cat_eat_sound;
extern Mix_Chunk* Dog_sound;
extern Mix_Chunk* Ting_sound;

//Mouse pos
extern int x_mouse;
extern int y_mouse;

#endif // !GLOBAL_H
