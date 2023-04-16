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
LTexture game_over_image;
LTexture background;
LTexture Font;
Enermy dog;
Enermy dog2;
Food pate;

bool GAME_OVER = false;
float avgFPS = 0;
float angle_arrow = 0;
int Score = 0;
int armo = 0; 
int Push_Count = 0;
Uint32 startTime = SDL_GetTicks();
stringstream cout_score;

LTexture gFPSTextTexture;
LTexture Arrow;

Mix_Music* Music_sound = NULL;
Mix_Chunk* Fire_sound = NULL;
Mix_Chunk* Lose_sound = NULL;
Mix_Chunk* cat_eat_sound = NULL;
Mix_Chunk* Dog_sound = NULL;
Mix_Chunk* Ting_sound = NULL;

//Mouse pos
int x_mouse = 0;
int y_mouse = 0;
