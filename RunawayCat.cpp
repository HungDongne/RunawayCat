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
			bool quit = false, GAME_OVER = false;

			//While application is running
			while (!quit && GAME_OVER == false)
			{
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
						//Mouse pos
						int x_mouse = 0, y_mouse = 0;
						SDL_GetMouseState(&x_mouse, &y_mouse);

						//Tính lực đẩy
						int push_x = -(x_mouse - cat.getX()) / 50 + cat.getXVelocity();
						int push_y = -(y_mouse - cat.getY()) / 50 + cat.getYVelocity();
						cout << push_x << " " << push_y << endl;

						cat.setVelocity(push_x, push_y);
						Push_Count--;
						
					}

				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render background to screen
				background.render(0, 0, NULL, 0, NULL, SDL_FLIP_NONE);

				//Here
				cat.render(cat.getX(), cat.getY(), NULL, 0, NULL, SDL_FLIP_NONE);
				pate.render(pate.getX(), pate.getY(), NULL, 0, NULL, SDL_FLIP_NONE);
				dog.render(dog.getX(), dog.getY(), NULL, 0, NULL, SDL_FLIP_NONE);
				//Font.render(5, 5, NULL, 0, NULL, SDL_FLIP_NONE);

				string cout_score = "Your Score: ";
				cout_score += to_string(Score);
				cout << cout_score << endl;
				Font.loadFromRenderedText(cout_score, 0, 0, 0);
				Font.render(5, 5, NULL, 0, NULL, SDL_FLIP_NONE);

				//Chuyển động
				cat.move();
				dog.move();

				//Kiểm tra va chạm
				if (checkCollision(cat, dog))
				{
					GAME_OVER = true;
				}
				if (checkCollision(cat, pate))
				{
					Score++;
					pate.renew();
					//cout << "Score: " << Score << endl;
				}

				//Nếu đã va chạm thì dừng lại
				if (GAME_OVER == true) {
					cat.loadFromFile("cat_cry.png");
					//cat.render(cat.getX(), cat.getY(), NULL, 0, NULL, SDL_FLIP_NONE);
					//cat_cry.render(cat.getX(), cat.getY(), NULL, 0, NULL, SDL_FLIP_NONE);
					game_over_image.render((SCREEN_WIDTH - game_over_image.getWidth()) / 2, (SCREEN_HEIGHT - game_over_image.getHeight()) / 2, NULL, 0, NULL, SDL_FLIP_NONE);
					//Update screen
					SDL_RenderPresent(gRenderer);
				}
				Push_Calculator();

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Delay time
	SDL_Delay(1000);

	//Free resources and close SDL
	close();

	return 0;
}