#include "LTexture.h"
#include "Enermy.h"
#include "Food.h"
#include "TextTexture.h"

using namespace std;

SDL_Surface* icon = NULL;
SDL_Cursor* cursor = NULL;
LTexture cat, mouse_computer, cat_cry, game_over_image, background;
Enermy dog;
Food pate;
int Score = 0, armo = 0, Push_Count = 0;
Uint32 startTime = SDL_GetTicks();
TextTexture Font;

bool init();
bool loadMedia();
void close();
bool checkCollision(LTexture& a, Enermy& b);
bool checkCollision(LTexture& a, Food& b);
void initialize();

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL couldn't initialize! SDL error: " << SDL_GetError() << endl;
		return false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		cout << "Warning: Linear texture filtering not enabled!" << endl;
	}

	gWindow = SDL_CreateWindow("KittyShot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		cout << "Window coundn't not be created! SDL error: " << SDL_GetError() << endl;
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL) {
		cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
		return false;
	}

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
		return false;
	}

	if (TTF_Init() == -1) {
		cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
		return false;
	}

	return true;
}

bool loadMedia() {
	bool success = true;

	// Tải hình ảnh background
	if (background.loadFromFile("background2.png") == false) {
		cout << "Failed to load background image" << endl;
		success = false;
	}

	//Load cat
	if (cat.loadFromFile("cat.png") == false) {
		cout << "Failed to load cat image!" << endl;
		success = false;
	}

	//Load dog1
	if (dog.loadFromFile("doggo.png") == false) {
		cout << "Failed to load doggo image!" << endl;
		success = false;
	}

	//Load game_over_image
	if (game_over_image.loadFromFile("game_over_image.png") == false) {
		cout << "Failed to load game_over_image!" << endl;
		success = false;
	}

	//Load cat_cry image
	if (cat_cry.loadFromFile("cat_cry.png") == false) {
		cout << "Failed to load cat_cry image!" << endl;
		success = false;
	}

	//Load food image
	if (pate.loadFromFile("pate.png") == false) {
		cout << "Failed to load food!" << endl;
		success = false;
	}

	//Open the font
	gFont = TTF_OpenFont("RunawayCat_Font.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	//Render text
	if (!Font.loadFromRenderedText("ZuThanhThao?", 0, 0, 0))
	{
		printf("Failed to render text texture!\n");
		success = false;
	}

	return success;
}

void close() {
	cat.free();
	dog.free();
	cat_cry.free();
	game_over_image.free();
	background.free();
	pate.free();
	Font.free();

	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	SDL_FreeSurface(icon);
	SDL_FreeCursor(cursor);
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

bool checkCollision(LTexture& a, Enermy& b) //Kiểm tra va chạm
{
	//Xác định vùng chồng lấp giữa 2 hình chữ nhật
	int leftA = a.getX();
	int rightA = a.getX() + a.getWidth();
	int topA = a.getY();
	int bottomA = a.getY() + a.getHeight();

	int leftB = b.getX();
	int rightB = b.getX() + b.getWidth();
	int topB = b.getY();
	int bottomB = b.getY() + b.getHeight();

	//Kiểm tra 2 hình chữ nhật có va chạm nhau hay không
	if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB)
	{
		return false;
	}

	//Trả về kết quả
	return true;
}

bool checkCollision(LTexture& a, Food& b) //Kiểm tra va chạm
{
	//Xác định vùng chồng lấp giữa 2 hình chữ nhật
	int leftA = a.getX();
	int rightA = a.getX() + a.getWidth();
	int topA = a.getY();
	int bottomA = a.getY() + a.getHeight();

	int leftB = b.getX();
	int rightB = b.getX() + b.getWidth();
	int topB = b.getY();
	int bottomB = b.getY() + b.getHeight();

	//Kiểm tra 2 hình chữ nhật có va chạm nhau hay không
	if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB)
	{
		return false;
	}

	//Trả về kết quả
	return true;
}

void Push_Calculator()
{	
	// Do something...
	Uint32 deltaTime = SDL_GetTicks() - startTime;
	int seconds = (float)deltaTime / 1000;
	Push_Count += seconds / 3;
}

void initialize()
{
	//Set seed for random
	srand(time(0));
	//Chỉnh sửa chuột máy tính
	SDL_Surface* icon = IMG_Load("popcat2_mini.png");
	SDL_Cursor* cursor = SDL_CreateColorCursor(icon, 0, 0);
	SDL_SetCursor(cursor);

	//Set food position
	pate.renew();

	//Position cat first append
	cat.setPos((SCREEN_WIDTH - cat.getWidth()) / 2, (SCREEN_HEIGHT - cat.getHeight()) / 2);
	cat.setVelocity(0, 1);
	int Score = 0;
	Push_Count = 1;
	
	//Set enermy velocity
	dog.setVelocity(0, 5);
	dog.setPos(rand() % (SCREEN_WIDTH - dog.getWidth()), -dog.getHeight());
}


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