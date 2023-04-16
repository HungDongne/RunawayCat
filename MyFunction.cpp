#include "MyFunction.h"


bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
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
	if (background.loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/background2.png") == false) {
		cout << "Failed to load background image" << endl;
		success = false;
	}

	//Load cat
	if (cat.loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/cat.png") == false) {
		cout << "Failed to load cat image!" << endl;
		success = false;
	}

	//Load dog1
	if (dog.loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/doggo.png") == false) {
		cout << "Failed to load doggo image!" << endl;
		success = false;
	}
	
	//Load dog2
	if (dog2.loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/doggo2.png") == false) {
		cout << "Failed to load doggo2 image!" << endl;
		success = false;
	}

	//Load game_over_image
	if (game_over_image.loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/game_over_image.png") == false) {
		cout << "Failed to load game_over_image!" << endl;
		success = false;
	}

	//Load food image
	if (pate.loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/pate.png") == false) {
		cout << "Failed to load food!" << endl;
		success = false;
	}

	//Load Arror image
	if (Arrow.loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/Gun.png") == false)
	{
		cout << "Failed to load Arrow image" << endl;
		success = false;
	}

	//Open the font
	gFont = TTF_OpenFont("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/fonts/Roboto-BlackItalic.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	//Render text
	if (!Font.loadFromRenderedText("RunawayCat?", 0, 0, 0))
	{
		printf("Failed to render text texture!\n");
		success = false;
	}

	//Load music
	Music_sound = Mix_LoadMUS("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/music/music.mp3");
	if (Music_sound == NULL) {
		cout << "Failed to load Music sound" << endl;
		success = false;
	}

	//Load Fire sound effect
	Fire_sound = Mix_LoadWAV("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/music/gun_fire_effect.wav");
	if (Fire_sound == NULL) {
		cout << "Failed to load Fire effect" << endl;
		success = false;
	}

	//Load Ting sound effect
	Ting_sound = Mix_LoadWAV("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/music/ting_sound.wav");
	if (Ting_sound == NULL) {
		cout << "Failed to load ting effect" << endl;
		success = false;
	}

	//Load lose sound effect
	Lose_sound = Mix_LoadWAV("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/music/lose_music.wav");
	if (Lose_sound == NULL) {
		cout << "Failed to load lose effect" << endl;
		success = false;
	}

	//Load dog sound effect
	Dog_sound = Mix_LoadWAV("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/music/dog_sound.wav");
	if (Dog_sound == NULL) {
		cout << "Failed to load dog effect" << endl;
		success = false;
	}

	//Load cat_eat sound effect
	cat_eat_sound = Mix_LoadWAV("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/music/cat_eat_sound.wav");
	if (cat_eat_sound == NULL) {
		cout << "Failed to load cat_eat effect" << endl;
		success = false;
	}

	return success;
}

void close() {
	//Free LTexture, image, enermy and food;
	cat.free();
	dog.free();
	dog2.free();
	game_over_image.free();
	background.free();
	pate.free();
	Font.free();
	gFPSTextTexture.free();
	Arrow.free();


	//Free sound
	Mix_FreeMusic(Music_sound);
	Music_sound = NULL;
	Mix_FreeChunk(Fire_sound);
	Fire_sound = NULL;
	Mix_FreeChunk(Lose_sound);
	Lose_sound = NULL;
	Mix_FreeChunk(cat_eat_sound);
	cat_eat_sound = NULL;
	Mix_FreeChunk(Dog_sound);
	Dog_sound = NULL;
	Mix_FreeChunk(Ting_sound);
	Ting_sound = NULL;

	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	Mix_CloseAudio();
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
	Uint32 deltaTime = SDL_GetTicks();
	//Uint32 deltaTime = SDL_GetTicks() - startTime;
	int seconds = (float)deltaTime / 1000;
	Push_Count += seconds / 1.5;
}

void initialize()
{
	//Set seed for random
	srand(time(0));
	//Chỉnh sửa chuột máy tính
	SDL_Surface* icon = IMG_Load("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/popcat2_mini.png");
	SDL_Cursor* cursor = SDL_CreateColorCursor(icon, 0, 0);
	SDL_SetCursor(cursor);

	//Set food position
	pate.renew();

	//Position cat first append
	cat.setPos((SCREEN_WIDTH - cat.getWidth()) / 2, (SCREEN_HEIGHT - cat.getHeight()) / 2);
	cat.setVelocity(0, 1);
	int Score = 0;
	Push_Count = 1;

	//Set enermy information
	dog.setVelocity(0, 1);
	dog2.setVelocity(0, 1);
	dog.setPos(rand() % (SCREEN_WIDTH - dog.getWidth()), -dog.getHeight());
	dog2.setPos(rand() % (SCREEN_WIDTH - dog2.getWidth()), -dog2.getHeight());
	Arrow.setPos((SCREEN_WIDTH - Arrow.getWidth()) / 2, (SCREEN_HEIGHT - Arrow.getHeight()) / 2);
}

double getAngle(double x, double y, double x0, double y0) {
	// Tính toán tọa độ mới
	x -= x0;
	y -= y0;
	// Tính góc
	return atan2(y, x) * 180 / M_PI;
}

void gamecalculator()
{
	//Mouse pos
	SDL_GetMouseState(&x_mouse, &y_mouse);

	//In memory text stream
	stringstream timeText;

	//Set text to be rendered
	timeText.str("");
	timeText << "FPS: " << fixed << setprecision(1) << avgFPS;

	//Render text
	if (!gFPSTextTexture.loadFromRenderedText(timeText.str().c_str(), 0, 0, 0))
	{
		printf("Unable to render FPS texture!\n");
	}

	//Chuyển động
	dog2.setVelocity(0, SDL_GetTicks() / 4000 + 1);
	cat.move();
	dog.move();
	dog2.move();

	//Calculator Arrow angle and position
	Arrow.setPos(cat.getX() - (Arrow.getWidth() - cat.getWidth()) / 2, cat.getY() - (Arrow.getHeight() - cat.getHeight()) / 2);
	angle_arrow = getAngle(x_mouse, y_mouse, Arrow.getX() + Arrow.getWidth() / 2, Arrow.getY() + Arrow.getHeight() / 2);

	cout_score.str("");
	cout_score << "YOUR SCORE: " << to_string(Score);
	Font.loadFromRenderedText(cout_score.str().c_str(), 0, 0, 0);

	//Kiểm tra va chạm
	if (checkCollision(cat, dog) || checkCollision(cat, dog2))
	{
		GAME_OVER = true;
	}
	if (checkCollision(cat, pate))
	{
		Mix_PlayChannel(-1, cat_eat_sound, 0);
		Mix_PlayChannel(-1, Ting_sound, 0);
		Score++;
		pate.renew();
	}

	//Nếu đã va chạm thì dừng lại
	if (GAME_OVER == true) {
		if (cat.loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/cat_cry.png") == false)
			cout << "Failed to load cat_cry image" << endl;
		Mix_PauseMusic();
		Mix_PlayChannel(-1, Lose_sound, 0);
	}
	Push_Calculator();
}

void gamerender()
{
	//Render background to screen
	background.render(0, 0, NULL, 0, NULL, SDL_FLIP_NONE);

	//Render
	pate.render(pate.getX(), pate.getY(), NULL, 0, NULL, SDL_FLIP_NONE);
	dog.render(dog.getX(), dog.getY(), NULL, 0, NULL, SDL_FLIP_NONE);
	dog2.render(dog2.getX(), dog2.getY(), NULL, 0, NULL, SDL_FLIP_NONE);
	cat.render(cat.getX(), cat.getY(), NULL, 0, NULL, SDL_FLIP_NONE);
	Arrow.render(Arrow.getX(), Arrow.getY(), NULL, angle_arrow, NULL, SDL_FLIP_NONE);
	if (GAME_OVER) game_over_image.render((SCREEN_WIDTH - game_over_image.getWidth()) / 2, (SCREEN_HEIGHT - game_over_image.getHeight()) / 2, NULL, 0, NULL, SDL_FLIP_NONE);


	//Render FPS
	gFPSTextTexture.render(5, 5 + Font.getHeight() + 5, NULL, 0, NULL, SDL_FLIP_NONE);
	Font.render(5, 5, NULL, 0, NULL, SDL_FLIP_NONE);
}

 