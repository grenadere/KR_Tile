#include "Tile.h"

Tile::Tile()
{
	window_rect.x = 0;
	window_rect.y = 0;
	window_rect.w = WIDTH;
	window_rect.h = HEIGTH;
	col = { 255,50,40,0 };
	init();
}

Tile::~Tile()
{
	SDL_DestroyTexture(T_IMG_1);
	SDL_DestroyTexture(T_IMG_2);
	SDL_DestroyTexture(T_IMG_3);
	SDL_DestroyTexture(T_IMG_4);
	SDL_DestroyTexture(background);
}

void Tile::init()
{
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGTH, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		cout << "SDL_CreateWindow Error:" << SDL_GetError() << endl;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
	}

	TTF_Init();
	SDL_Surface* bk_surf = IMG_Load("background.jpg");
	SDL_Surface* IMG_1 = IMG_Load("img1.jpg");
	SDL_Surface* IMG_2 = IMG_Load("img2.jpg");
	SDL_Surface* IMG_3 = IMG_Load("img3.jpg");
	SDL_Surface* IMG_4 = IMG_Load("img4.jpg");
	if (bk_surf == nullptr)
	{
		cout << "SDL_CreateWindow Error:" << SDL_GetError() << endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "IMG Error", "Background not found", window);
	}
	if ((IMG_1 == nullptr) && (IMG_2 == nullptr) && (IMG_3 == nullptr) && (IMG_4 == nullptr))
	{
		cout << "SDL_CreateWindow Error:" << SDL_GetError() << endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "IMG Error", "No image", window);
	}
	background = SDL_CreateTextureFromSurface(renderer, bk_surf);
	T_IMG_1 = SDL_CreateTextureFromSurface(renderer, IMG_1);
	T_IMG_2 = SDL_CreateTextureFromSurface(renderer, IMG_2);
	T_IMG_3 = SDL_CreateTextureFromSurface(renderer, IMG_3);
	T_IMG_4 = SDL_CreateTextureFromSurface(renderer, IMG_4);

	SDL_Rect rect_img_1 = { 200, 125, 400, 225 };
	SDL_Rect rect_img_2 = { 1000, 125, 400, 225 };
	SDL_Rect rect_img_3 = { 200, 500, 400, 225 };
	SDL_Rect rect_img_4 = { 1000, 500, 400, 225 };

	SDL_RenderCopy(renderer, background, NULL, &window_rect);
	SDL_RenderCopy(renderer, T_IMG_1, NULL, &rect_img_1);
	SDL_RenderCopy(renderer, T_IMG_2, NULL, &rect_img_2);
	SDL_RenderCopy(renderer, T_IMG_3, NULL, &rect_img_3);
	SDL_RenderCopy(renderer, T_IMG_4, NULL, &rect_img_4);



	string str = "Choose image";
	TTF_Font* font = TTF_OpenFont("19440.ttf", 100);
	SDL_Surface* text = TTF_RenderText_Solid(font, str.c_str(), col);
	SDL_Texture* TX_text = SDL_CreateTextureFromSurface(renderer, text);


	SDL_Rect rect_text = { 600, 400, 400, 100 };
	SDL_RenderCopy(renderer, TX_text, NULL, &rect_text);

	SDL_RenderPresent(renderer);

	SDL_FreeSurface(bk_surf);
	SDL_FreeSurface(IMG_1);
	SDL_FreeSurface(IMG_2);
	SDL_FreeSurface(IMG_3);
	SDL_FreeSurface(IMG_4);
	SDL_FreeSurface(text);

	SDL_DestroyTexture(TX_text);
}

void Tile::Button(int x, int y)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "IMG ne Error", "norma image", window);
}
