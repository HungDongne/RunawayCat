#include "Global.h"
#include "Constant.h"
#include "MyFunction.h"
#include "LTexture.h"
#include "Enermy.h"
#include "Food.h"

using namespace std;

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		cout << "Failed to initialize!" << endl;
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			cout << "Failed to load media!" << endl;
		}
		else
		{
			//Event handler
			SDL_Event e;

			//Khởi tạo
			initialize();

			//Main loop flag
			bool quit = false;

			//The frames per second timer
			LTimer fpsTimer;

			//The frames per second cap timer
			LTimer capTimer;

			//Start counting frames per second
			int countedFrames = 0;
			fpsTimer.start();
			Mix_PlayMusic(Music_sound, -1);

			//While application is running
			while (!quit && GAME_OVER == false)
			{
				//Start cap timer
				capTimer.start();
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						//SDL_Delay(3000);
						quit = true;
					}
					if (e.type == SDL_MOUSEBUTTONDOWN && Push_Count > 0)
					{
						Mix_PlayChannel(-1, Fire_sound, 0);
						startTime = SDL_GetTicks();
						//Tính lực đẩy
						int push_x = -(x_mouse - cat.getX()) / 50 + cat.getXVelocity();
						int push_y = -(y_mouse - cat.getY()) / 50 + cat.getYVelocity();
						cat.setVelocity(push_x, push_y);
						Push_Count--;
					}
				}
				//Calculate and correct fps
				avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
				if (avgFPS > 2000000)
				{
					avgFPS = 0;
				}			
				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				gamecalculator();
				gamerender();

				//Update screen
				SDL_RenderPresent(gRenderer);
				++countedFrames;
				
				//If frame finished early
				int frameTicks = capTimer.getTicks();
				if (frameTicks < SCREEN_TICK_PER_FRAME)
				{
					//Wait remaining time
					SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
				}
			}
		}
	}

	//Delay time
	SDL_Delay(1000);
	//Free resources and close SDL
	close();
	return 0;
}