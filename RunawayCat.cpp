#include "Global.h"
#include "Constant.h"
#include "MyFunction.h"
#include "LTexture.h"
#include "Enermy.h"
#include "Food.h"

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
			SDL_Event e;
			initialize();
			bool START_GAME = false;
			while (quit == false)
			{
				while (GAME_OVER == true && quit == false)
				{
					while (SDL_PollEvent(&e) != 0)
					{
						if (e.type == SDL_QUIT)
						{
							quit = true;
							GAME_OVER = false;
						}
						if (e.type == SDL_KEYDOWN)
						{
							if (e.key.keysym.sym == SDLK_SPACE) GAME_OVER = false;
							if (e.key.keysym.sym == SDLK_KP_ENTER) GAME_OVER = false;
							if (e.key.keysym.sym == SDLK_RETURN) GAME_OVER = false;
						}
						if (e.type == SDL_MOUSEBUTTONDOWN)
						{
							SDL_GetMouseState(&x_mouse, &y_mouse);

							int i = 1;
							if (checkCollision(x_mouse, y_mouse, restart))
							{
								cout << i << endl;
								i++;
								cout << restart.getX() << " " << restart.getY() << endl;
							}
						}
					}

					SDL_RenderClear(gRenderer);
					restart.render(restart.getX(), restart.getY(), NULL, 0, NULL, SDL_FLIP_NONE);

					string tmp_string = "Press SPACE/ENTER to RESTART";
					Font.loadFromRenderedText(tmp_string, 0, 0, 0);
					Font.render((SCREEN_WIDTH - Font.getWidth()) / 2, (SCREEN_HEIGHT - Font.getHeight()) / 2 + 310, NULL, 0, NULL, SDL_FLIP_NONE);

					tmp_string = "YOUR HIGHEST SCORE: " + to_string(highest_score);
					Font.loadFromRenderedText(tmp_string, 0, 0, 0);
					Font.render((SCREEN_WIDTH - Font.getWidth()) / 2, 60);

					SDL_RenderPresent(gRenderer);
				}
				initialize();
				if (quit == false) Mix_PlayMusic(Music_sound, -1);
				while (GAME_OVER == false && quit == false)
				{
					while (SDL_PollEvent(&e) != 0)
					{
						if (e.type == SDL_QUIT)
						{
							quit = true;
							GAME_OVER = true;
						}
						if (e.type == SDL_MOUSEBUTTONDOWN && bullet_count > 0)
						{
							Mix_PlayChannel(-1, Fire_sound, 0);
							//Tính lực đẩy
							tmp_time = SDL_GetTicks();
							int push_x = -(x_mouse - cat.getX()) / 45 + cat.getXVelocity();
							int push_y = -(y_mouse - cat.getY()) / 45 + cat.getYVelocity();
							cat.setVelocity(push_x, push_y);
							bullet_count--;
							press_mouse = true;
						}
					}
					//Clear screen
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(gRenderer);
					gamecalculator();
					gamerender();

					//Update screen
					SDL_RenderPresent(gRenderer);
				}
				SDL_Delay(1000);
			}
		}
	}

	SDL_Delay(1000);
	close();
	return 0;
}