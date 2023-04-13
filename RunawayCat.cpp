#include "LTexture.h"
using namespace std;

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

SDL_Surface* icon = NULL;
SDL_Cursor* cursor = NULL;
LTexture cat, mouse_computer, cat_cry, game_over_image, background;

//-------------------------Enermy class------------------------
class Enermy
{
public:
	//Initializes variables
	Enermy();

	//Deallocates memory
	~Enermy();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

	// Set velocity
	void setVelocity(int vx, int vy);

	// Get velocity in x and y direction
	int getXVelocity();
	int getYVelocity();

	// Get position
	int getX();
	int getY();

	void move();

	void setPos(int x, int y);

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;

	int mPosX, mPosY;
	int mVelX, mVelY;

	bool renew_flag;
};

Enermy dog;

Enermy::Enermy()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mPosX = 0;
	mPosY = 0;
	mVelX = 0;
	mVelY = 0;
	renew_flag = false;
}

Enermy::~Enermy()
{
	//Deallocate
	free();
}

bool Enermy::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void Enermy::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Enermy::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void Enermy::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void Enermy::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void Enermy::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int Enermy::getWidth()
{
	return mWidth;
}

int Enermy::getHeight()
{
	return mHeight;
}

void Enermy::setVelocity(int vx, int vy) {
	mVelX = vx;
	mVelY = vy;
}

int Enermy::getX() {
	return mPosX;
}

int Enermy::getY() {
	return mPosY;
}

void Enermy::move() {
	mPosX += mVelX;
	mPosY += mVelY;

	//cout << "PosY: " << mPosY << " SCREEN_HEIGHT: " <<  SCREEN_HEIGHT << endl;

	if (mPosY > SCREEN_HEIGHT)
	{
		renew_flag = true;
	}

	if (renew_flag)
	{
		renew_flag = false;
		mPosX = rand() % (SCREEN_WIDTH - mWidth);
		mPosY = -mHeight - 50;
	}

	/*
	// Giới hạn vị trí của Enermy trong khu vực của cửa sổ
	if (mPosX < 0) {
		mVelX = -mVelX;
		//mPosX = 0;
	}
	else if (mPosX > SCREEN_WIDTH - mWidth) {
		mVelX = -mVelX;
		//mPosX = SCREEN_WIDTH - mWidth;
	}

	if (mPosY < 0) {
		mVelY = -mVelY;
		//mPosY = 0;
	}
	else if (mPosY > SCREEN_HEIGHT - mHeight) {
		mVelY = -mVelY;
		//mPosY = SCREEN_HEIGHT - mHeight;
	}
	*/
}

void Enermy::setPos(int x, int y) {
	mPosX = x;
	mPosY = y;
}

int Enermy::getXVelocity()
{
	return mVelX;
}

int Enermy::getYVelocity()
{
	return mVelY;
}

//--------------------------------------------------------------
bool init();
bool loadMedia();
void close();
bool checkCollision(LTexture& a, Enermy& b);
void initialize();

//--------------------------------------------------------------
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
	if (background.loadFromFile("background.png") == false) {
		cout << "Failed to load background image" << endl;
	}

	//Load cat
	if (cat.loadFromFile("cat.png") == false) {
		cout << "Failed load cat!" << endl;
	}

	//Load dog1
	if (dog.loadFromFile("doggo.png") == false) {
		cout << "Failed load doggo!" << endl;
	}

	//Load game_over_image
	if (game_over_image.loadFromFile("game_over_image.png") == false) {
		cout << "Failed load game_over_image!" << endl;
	}

	//Load cat_cry
	if (cat_cry.loadFromFile("cat_cry.png") == false) {
		cout << "Failed cat_cry!" << endl;
	}

	/*
	//Tải hình ảnh character
	SDL_Surface* loadedSurface = IMG_Load("my_cat.png");
	if (loadedSurface == nullptr) {
		cout << "Unable to load image! SDL Error: " << SDL_GetError() << endl;
		success = false;
	}
	else {
		Character = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (Character == nullptr) {
			cout << "Unable to create texture from image! SDL Error: " << SDL_GetError() << endl;
			success = false;
		}

		SDL_FreeSurface(loadedSurface);
	}
	*/

	return success;
}

void close() {
	cat.free();
	dog.free();
	cat_cry.free();
	game_over_image.free();
	background.free();

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	SDL_FreeSurface(icon);
	SDL_FreeCursor(cursor);
	IMG_Quit();
	SDL_Quit();
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

void initialize()
{
	//Chỉnh sửa chuột máy tính
	SDL_Surface* icon = IMG_Load("popcat2_mini.png");
	SDL_Cursor* cursor = SDL_CreateColorCursor(icon, 0, 0);
	SDL_SetCursor(cursor);

	//Position cat first append
	cat.setPos((SCREEN_WIDTH - cat.getWidth()) / 2, (SCREEN_HEIGHT - cat.getHeight()) / 2);
	cat.setVelocity(0, 1);

	srand(time(0));

	//cout << "Now time is: " << time(0) << endl;

	//Set enermy velocity
	dog.setVelocity(0, 4);
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
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						//Mouse pos
						int x_mouse = 0, y_mouse = 0;
						SDL_GetMouseState(&x_mouse, &y_mouse);

						//Tính lực đẩy
						int push_x = -(x_mouse - cat.getX()) / 50 + cat.getXVelocity();
						int push_y = -(y_mouse - cat.getY()) / 50 + cat.getYVelocity();
						cout << push_x << " " << push_y << endl;

						cat.setVelocity(push_x, push_y);
					}

				}

				//Kiểm tra va chạm
				if (checkCollision(cat, dog))
				{
					GAME_OVER = true;
				}

				//Nếu đã va chạm thì dừng lại
				if (GAME_OVER == true) {
					//(cat_cry.render(cat.getX(), cat.getY(), NULL, 0, NULL, SDL_FLIP_NONE);
					//game_over_image.render((SCREEN_WIDTH - game_over_image.getWidth()) / 2, (SCREEN_HEIGHT - game_over_image.getHeight()) / 2, NULL, 0, NULL, SDL_FLIP_NONE);
					//Load cat_cry
					if (cat_cry.loadFromFile("cat_cry.png") == false) {
						cout << "Failed cat_cry!" << endl;
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render background to screen
				background.render(0, 0, NULL, 0, NULL, SDL_FLIP_NONE);

				//Here
				cat.render(cat.getX(), cat.getY(), NULL, 0, NULL, SDL_FLIP_NONE);
				dog.render(dog.getX(), dog.getY(), NULL, 0, NULL, SDL_FLIP_NONE);

				//Chuyển động
				cat.move();
				dog.move();

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