#include "Global.h"
#include "Constant.h"
#include "MyFunction.h"
#include "LTexture.h"
#include "Enermy.h"
#include "Food.h"
#include "LoadFile.h"

using namespace std;


int main(int argc, char* args[])
{
	if (!init())
	{
		cout << "Failed to initialize!" << endl;
	}
	else
	{
		if (!loadMedia())
		{
			cout << "Failed to load media!" << endl;
		}
		else
		{
			highest_score = 0;
			bool quit = false;
			initialize();
			while (quit == false)
			{
				//MENU_MODE
				Music_sound = Mix_LoadMUS("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/music/music-menu.mp3");
				Mix_PlayMusic(Music_sound, -1);
				while (GAME_OVER == true && quit == false)
				{
					while (SDL_PollEvent(&e) != 0)
					{
						if (e.type == SDL_QUIT)
						{
							quit = true;
							GAME_OVER = true;
						}
						if (e.type == SDL_MOUSEBUTTONDOWN)
						{
							SDL_GetMouseState(&x_mouse, &y_mouse);
							if (checkCollision(x_mouse, y_mouse, music_menu))
							{
								music_config();
							}
							if (checkCollision(x_mouse, y_mouse, how_to_play_title[0]))
							{
								GAME_OVER = false;
							}
							if (checkCollision(x_mouse, y_mouse, how_to_play_title[1]))
							{
								how_to_play_flag = true;
							}
							if (checkCollision(x_mouse, y_mouse, how_to_play_title[2]))
							{
								quit = true;
								GAME_OVER = true;
							}
						}
						//HOW_TO_PLAY_MODE
						tmp_texture.loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/how_to_play.png");
						turn_left = true, turn_right = false;
						while (how_to_play_flag == true && quit == false)
						{
							SDL_RenderClear(gRenderer);
							while (SDL_PollEvent(&e) != 0)
							{
								if (e.type == SDL_KEYDOWN)
								{
									if (e.key.keysym.sym == SDLK_RETURN)
									{
										how_to_play_flag = false;
									}
									if (e.key.keysym.sym == SDLK_LEFT)
									{
										turn_left = true;
										turn_right = false;
									}
									if (e.key.keysym.sym == SDLK_RIGHT)
									{
										turn_right = true;
										turn_left = false;
									}
								}
								if (e.type == SDL_QUIT)
								{
									quit = true;
								}
								if (e.type == SDL_MOUSEBUTTONDOWN)
								{
									SDL_GetMouseState(&x_mouse, &y_mouse);
									if (checkCollision(x_mouse, y_mouse, music_menu))
									{
										music_config();
									}
									if (checkCollision(x_mouse, y_mouse, return_button))
									{
										how_to_play_flag = false;
									}
									if (checkCollision(x_mouse, y_mouse, left_arrow_image))
									{
										turn_left = true;
										turn_right = false;
									}
									if (checkCollision(x_mouse, y_mouse, right_arrow_image))
									{
										turn_left = false;
										turn_right = true;
									}
								}
							}
							if (turn_right && tmp_texture.getX() >= -(tmp_texture.getWidth() - SCREEN_WIDTH))
							{
								tmp_texture.setPos(tmp_texture.getX() - 12, tmp_texture.getY());
							}
							if (turn_left && tmp_texture.getX() <= 0)
							{
								tmp_texture.setPos(tmp_texture.getX() + 12, tmp_texture.getY());
							}
							how_to_play_mode();
							SDL_RenderPresent(gRenderer);
						}
					}

					SDL_RenderClear(gRenderer);
					menu_mode();
					SDL_RenderPresent(gRenderer);
				}
				
				//PLAY MODE
				initialize();
				while (GAME_OVER == false && quit == false)
				{
					while (SDL_PollEvent(&e) != 0)
					{
						if (e.type == SDL_QUIT)
						{
							quit = true;
							GAME_OVER = true;
						}
						if (e.type == SDL_MOUSEBUTTONDOWN)
						{
							SDL_GetMouseState(&x_mouse, &y_mouse);
							if (checkCollision(x_mouse, y_mouse, music_menu))
							{
								music_config();
							} else if (checkCollision(x_mouse, y_mouse, return_button))
								{
									GAME_OVER = true;
								}
							else if (bullet_count > 0)
								{
									Mix_PlayChannel(-1, Fire_sound, 0);
									tmp_time = SDL_GetTicks();
									int push_x = -(x_mouse - cat.getX()) / 45 + cat.getXVelocity();
									int push_y = -(y_mouse - cat.getY()) / 45 + cat.getYVelocity();
									cat.setVelocity(push_x, push_y);
									bullet_count--;
									press_mouse = true;
								}
							else Mix_PlayChannel(-1, cant_shot_sound, 0);
						}
					}
					SDL_RenderClear(gRenderer);
					gamecalculator();
					gamerender();
					SDL_RenderPresent(gRenderer);
				}
				SDL_Delay(1000);
			}
		}
	}

	SDL_Delay(500);
	close();
	return 0;
}