#include "LoadFile.h"

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "SDL couldn't ! SDL error: " << SDL_GetError() << endl;
		return false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		cout << "Warning: Linear texture filtering not enabled!" << endl;
	}

	gWindow = SDL_CreateWindow("RunawayCat", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

	if (gun_fire_effect.loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/gun_fire_effect.png") == false)
	{
		cout << "Failed to load gun fire effect" << endl;
		success = false;
	}

	if (bullet_image.loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/bullet.png") == false)
	{
		cout << "Failed to load bullet image" << endl;
		success = false;
	}

	if (treasure.loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/treasure.png") == false)
	{
		cout << "Failed to load treasure image" << endl;
		success = false;
	}

	if (restart.loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/wonderful.png") == false)
	{
		cout << "Failed to load restart image" << endl;
		success = false;
	}

	if (music_menu.loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/music-on.png") == false)
	{
		cout << "Failed to load music-menu image" << endl;
		success = false;
	}


	if (how_to_play_title[0].loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/title.png") == false)
	{
		cout << "Failed to load how-to-play-menu image" << endl;
		success = false;
	}

	if (how_to_play_title[1].loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/title.png") == false)
	{
		cout << "Failed to load how-to-play-menu image" << endl;
		success = false;
	}

	if (how_to_play_title[2].loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/title.png") == false)
	{
		cout << "Failed to load how-to-play-menu image" << endl;
		success = false;
	}

	if (return_button.loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/return_button.png") == false)
	{
		cout << "Failed to load return button image" << endl;
		success = false;
	}

	if (score_image.loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/score.png") == false)
	{
		cout << "Failed to load score image" << endl;
		success = false;
	}

	if (left_arrow_image.loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/left_arrow.png") == false)
	{
		cout << "Failed to load left arrow image" << endl;
		success = false;
	}

	if (right_arrow_image.loadFromFile("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/images/right_arrow.png") == false)
	{
		cout << "Failed to load right arrow image" << endl;
		success = false;
	}

	music_menu.setPos(SCREEN_WIDTH - music_menu.getWidth() - 20, 20);
	return_button.setPos(20, 20);
	left_arrow_image.setPos(20, (SCREEN_HEIGHT - left_arrow_image.getHeight()) / 2);
	right_arrow_image.setPos(SCREEN_WIDTH - 20 - right_arrow_image.getWidth(), (SCREEN_HEIGHT - right_arrow_image.getHeight()) / 2);

	//Open the font
	gFont = TTF_OpenFont("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/fonts/Minecraft.ttf", 24);
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

	//Load can't shoot effect
	cant_shot_sound = Mix_LoadWAV("C:/Users/Admin/Desktop/Code/C++/RunawayCat/data/music/cant_shot.wav");
	if (cant_shot_sound == NULL) {
		cout << "Failed to load can't shoot effect" << endl;
		success = false;
	}

	return success;
}

void close() {

	cat.free();
	dog.free();
	dog2.free();
	game_over_image.free();
	background.free();
	pate.free();
	Font.free();
	gFPSTextTexture.free();
	Arrow.free();
	restart.free();
	bullet_image.free();
	tmp_texture.free();
	treasure.free();
	music_menu.free();
	how_to_play_title[0].free();
	how_to_play_title[1].free();
	how_to_play_title[2].free();
	return_button.free();
	score_image.free();
	left_arrow_image.free();
	right_arrow_image.free();

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
	Mix_FreeChunk(cant_shot_sound);
	cant_shot_sound = NULL;

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