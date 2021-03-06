#include "Tile.h"

Tile::Tile()
{
	TTF_Init();
	Game_State = choose_img;
	window_rect.x = 0;
	window_rect.y = 0;
	window_rect.w = WIDTH;
	window_rect.h = HEIGTH;
	window = nullptr;
	renderer = nullptr;
	background = nullptr;
	clip = nullptr;
	clip_for_check = nullptr;
	Surf_Target_IMG = nullptr;
	IMG_1 = nullptr;
	IMG_2 = nullptr;
	IMG_3 = nullptr;
	IMG_4 = nullptr;
	Target_IMG = nullptr;
	T_IMG_1 = nullptr;
	T_IMG_2 = nullptr;
	T_IMG_3 = nullptr;
	T_IMG_4 = nullptr;
	cells_x = 0;
	cells_y = 0; 
	choose_image = -1;
	color_text = { 255,140,0,0 };
	cursor_x = -1;
	cursor_y = -1;
	init();
}

Tile::~Tile()
{
	if (clip != nullptr)
	{
		for (int i = 0; i < cells_x; i++)
		{
			delete[] clip[i];
			delete[] clip_for_check[i];
		}
		delete[] clip;
		delete[] clip_for_check;
	}
	SDL_FreeSurface(IMG_1);
	SDL_FreeSurface(IMG_2);
	SDL_FreeSurface(IMG_3);
	SDL_FreeSurface(IMG_4);
	SDL_DestroyTexture(T_IMG_1);
	SDL_DestroyTexture(T_IMG_2);
	SDL_DestroyTexture(T_IMG_3);
	SDL_DestroyTexture(T_IMG_4);
	SDL_DestroyTexture(background);
	SDL_DestroyWindow(window);
	TTF_Quit();
}

void Tile::init()
{
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGTH, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateWindow Error", SDL_GetError(), window);
		exit(1);
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateRenderer Error", SDL_GetError(), window);
		exit(1);
	}
	SDL_RenderClear(renderer);
	SDL_Surface* bk_surf = IMG_Load("background.jpg");
	IMG_1 = IMG_Load("img1.jpg");
	IMG_2 = IMG_Load("img2.jpg");
	IMG_3 = IMG_Load("img3.jpg");
	IMG_4 = IMG_Load("img4.jpg");
	if (bk_surf == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "IMG Error", "Background not found", window);
		exit(1);
	}
	if ((IMG_1 == nullptr) && (IMG_2 == nullptr) && (IMG_3 == nullptr) && (IMG_4 == nullptr))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "IMG Error", "No image", window);
		exit(1);
	}
	background = SDL_CreateTextureFromSurface(renderer, bk_surf);
	if(IMG_1 != nullptr)
		T_IMG_1 = SDL_CreateTextureFromSurface(renderer, IMG_1);
	if (IMG_2 != nullptr)
		T_IMG_2 = SDL_CreateTextureFromSurface(renderer, IMG_2);
	if (IMG_3 != nullptr)
		T_IMG_3 = SDL_CreateTextureFromSurface(renderer, IMG_3);
	if (IMG_4 != nullptr)
		T_IMG_4 = SDL_CreateTextureFromSurface(renderer, IMG_4);

	SDL_FreeSurface(bk_surf);
}

void Tile::Button_Click(int x, int y)
{
	
	int width;
	int height;
	SDL_Texture* texture;
	SDL_Texture* Back;
	switch (Game_State)
	{
	case choose_img:

		if ((x > 200) && (x < 600) && (y > 125) && (y < 350) && (T_IMG_1 != nullptr))
		{
			Surf_Target_IMG = IMG_1;
			Target_IMG = T_IMG_1;
			Game_State = choose_cells;
		}
		if ((x > 1000) && (x < 1400) && (y > 125) && (y < 350) && (T_IMG_2 != nullptr))
		{
			Surf_Target_IMG = IMG_2;
			Target_IMG = T_IMG_2;
			Game_State = choose_cells;
		}
		if ((x > 200) && (x < 600) && (y > 500) && (y < 725) && (T_IMG_3 != nullptr))
		{
			Surf_Target_IMG = IMG_3;
			Target_IMG = T_IMG_3;
			Game_State = choose_cells;
		}
		if ((x > 1000) && (x < 1400) && (y > 500) && (y < 725) && (T_IMG_4 != nullptr))
		{
			Surf_Target_IMG = IMG_4;
			Target_IMG = T_IMG_4;
			Game_State = choose_cells;
		}
		break;
	case choose_cells:
		if ((cells_x < 0) || (cells_x > 9) || (cells_y < 0) || (cells_y > 9) || ((cells_x == 0) && (cells_y == 0)))
			break;
		width = Surf_Target_IMG->w;
		height = Surf_Target_IMG->h;
		texture = SDL_CreateTextureFromSurface(renderer, Surf_Target_IMG);
		cells_x++;
		cells_y++;
		try
		{
			clip = new SDL_Texture * *[cells_x];
			clip_for_check = new SDL_Texture * *[cells_x];
			for (int i = 0; i < cells_x; i++)
			{
				clip[i] = new SDL_Texture * [cells_y];
				clip_for_check[i] = new SDL_Texture * [cells_y];
			}
		}
		catch (std::bad_alloc)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "RAM Error", "Not enough RAM", window);
			exit(1);
		}
		Back = SDL_GetRenderTarget(renderer);
		for (int i = 0; i < cells_x; i++)
		{
			for (int j = 0; j < cells_y; j++)
			{
				clip[i][j] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width / cells_x, height / cells_y);
				clip_for_check[i][j] = clip[i][j];
				SDL_SetTextureBlendMode(clip[i][j], SDL_BLENDMODE_BLEND);
				SDL_Rect rect = { i * width / cells_x,j * height / cells_y, width / cells_x, height / cells_y };
				SDL_SetRenderTarget(renderer, clip[i][j]);
				SDL_RenderCopy(renderer, texture, &rect, NULL);

			}
		}
		srand(time(NULL));
		do
		{
			for (int i = 0; i < 1000; i++)
				swap_clip(rand() % cells_x, rand() % cells_y, rand() % cells_x, rand() % cells_y);
		} while (!check_tile());
		SDL_SetRenderTarget(renderer, Back);
		SDL_DestroyTexture(texture);
		SDL_DestroyTexture(Back);
		Game_State = game;
		break;
	case game:
		if ((((x - MARGIN_LEFT) / (WIDTH_IMG / cells_x)) < 0) || (((x - MARGIN_LEFT) / (WIDTH_IMG / cells_x)) >= cells_x) ||
			(((y - MARGIN_TOP) / (HEIGTH_IMG / cells_y)) < 0) || (((y - MARGIN_TOP) / (HEIGTH_IMG / cells_y)) >= cells_y))
			break;
		if ((cursor_x == -1) && (cursor_y == -1))
		{
			cursor_x = (x - MARGIN_LEFT) / (WIDTH_IMG / cells_x);
			cursor_y = (y - MARGIN_TOP) / (HEIGTH_IMG / cells_y);
		}
		else
		{
			swap_clip(cursor_x, cursor_y, (x - MARGIN_LEFT) / (WIDTH_IMG / cells_x), (y - MARGIN_TOP) / (HEIGTH_IMG / cells_y));
			cursor_x = -1;
			cursor_y = -1;
		}
		if (!check_tile())
			Game_State = win;
		break;
	case win:
		if ((x > WIDTH - MARGIN_LEFT - WIDTH_ICON) && (x < WIDTH - MARGIN_LEFT) &&
			(y > MARGIN_TOP + HEIGTH_IMG - HEIGTH_ICON / 2) && (y < MARGIN_TOP + HEIGTH_IMG))
			Game_State = choose_img;
	default:
		break;
	}
}

void Tile::Button_Mov(int x, int y)
{
	switch (Game_State)
	{
	case choose_img:
		if ((x > 200) && (x < 600) && (y > 125) && (y < 350) && (T_IMG_1 != nullptr))
		{
			choose_image = 0;
			break;
		}
		if ((x > 1000) && (x < 1400) && (y > 125) && (y < 350) && (T_IMG_2 != nullptr))
		{
			choose_image = 1;
			break;
		}
		if ((x > 200) && (x < 600) && (y > 500) && (y < 725) && (T_IMG_3 != nullptr))
		{
			choose_image = 2;
			break;
		}
		if ((x > 1000) && (x < 1400) && (y > 500) && (y < 725) && (T_IMG_4 != nullptr))
		{
			choose_image = 3;
			break;
		}
		choose_image = -1;
		break;
	case choose_cells:
		if ((x > 550) && (x < 1060) && (y > 200) && (y < 710))
		{
			cells_x = (x - 550) / 50;
			cells_y = (y - 200) / 50;
		}
		else
		{
			cells_x = -1;
			cells_y = -1;
		}
		break;
	default:
		break;
	}
	return;
}

void Tile::Draw()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, &window_rect);
	switch (Game_State)
	{
	case choose_img:
		Draw_Start();
		break;
	case choose_cells:
		Draw_Cels();
		break;
	case game:
		Draw_Game();
		break;
	case win:
		Draw_Win();
		break;
	default:
		break;
	}
	SDL_RenderPresent(renderer);
}

void Tile::swap_clip(int x1, int y1, int x2, int y2)
{
	SDL_Texture* tmp = clip[x1][y1];
	clip[x1][y1] = clip[x2][y2];
	clip[x2][y2] = tmp;
}

bool Tile::check_tile()
{
	for (int i = 0; i < cells_x; i++)
		for (int j = 0; j < cells_y; j++)
			if (clip[i][j] != clip_for_check[i][j])
				return true;
	return false;
}

void Tile::Draw_Start()
{

	SDL_Rect rect_img[4] = { { 200, 125, 400, 225 },
							{ 1000, 125, 400, 225 },
							{ 200, 550, 400, 225 },
							{ 1000, 550, 400, 225 } };
	if (choose_image > -1)
	{
		rect_img[choose_image].x -= 50;
		rect_img[choose_image].y -= 50;
		rect_img[choose_image].h += 100;
		rect_img[choose_image].w += 100;
	}

	SDL_RenderCopy(renderer, background, NULL, &window_rect);
	SDL_RenderCopy(renderer, T_IMG_1, NULL, &rect_img[0]);
	SDL_RenderCopy(renderer, T_IMG_2, NULL, &rect_img[1]);
	SDL_RenderCopy(renderer, T_IMG_3, NULL, &rect_img[2]);
	SDL_RenderCopy(renderer, T_IMG_4, NULL, &rect_img[3]);

	string str = "Choose image";
	TTF_Font* font = TTF_OpenFont("19440.ttf", 100);
	if (font == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "TTF Error", SDL_GetError(), window);
		exit(1);
	}
	SDL_Surface* text = TTF_RenderText_Solid(font, str.c_str(), color_text);
	SDL_Texture* TX_text = SDL_CreateTextureFromSurface(renderer, text);
	SDL_Rect rect_text = { 600, 400, 400, 100 };
	SDL_RenderCopy(renderer, TX_text, NULL, &rect_text);

	SDL_FreeSurface(text);

	SDL_DestroyTexture(TX_text);

}

void Tile::Draw_Cels()
{
	SDL_Rect back_rect = { 544, 189, 511, 511 };
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(renderer, &back_rect);
	for (int i = 0; i < MAX_CELLS; i++)
	{
		for (int j = 0; j < MAX_CELLS; j++)
		{
			SDL_Rect rect = { 545 + i * 51, 190 + j * 51, 50, 50 };
			if ((i <= cells_x) && (j <= cells_y))
				SDL_SetRenderDrawColor(renderer, 50, 255, 40, 0xFF);
			else
				SDL_SetRenderDrawColor(renderer, 40, 50, 255, 0xFF);
			SDL_RenderFillRect(renderer, &rect);
		}
	}
	string str = "Choose size cells";
	TTF_Font* font = TTF_OpenFont("19440.ttf", 100);
	if (font == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "TTF Error", SDL_GetError(), window);
		exit(1);
	}
	SDL_Surface* text = TTF_RenderText_Solid(font, str.c_str(), color_text);
	SDL_Texture* TX_text = SDL_CreateTextureFromSurface(renderer, text);
	SDL_Rect rect_text = { 545, 100, 510, 90 };

	SDL_RenderCopy(renderer, TX_text, NULL, &rect_text);

	SDL_FreeSurface(text);

	SDL_DestroyTexture(TX_text);
}

void Tile::Draw_Game()
{
	SDL_Rect icon_rect = { WIDTH - MARGIN_LEFT - WIDTH_ICON, MARGIN_TOP, WIDTH_ICON, HEIGTH_ICON };
	SDL_Rect back_rect = { MARGIN_LEFT, MARGIN_TOP, WIDTH_IMG, HEIGTH_IMG };
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0);
	SDL_RenderFillRect(renderer, &back_rect);
	SDL_RenderCopy(renderer, Target_IMG, NULL, &icon_rect);

	for (int i = 0; i < cells_x; i++)
	{
		for (int j = 0; j < cells_y; j++)
		{
			SDL_Rect rect = { MARGIN_LEFT + i * (WIDTH_IMG / cells_x), MARGIN_TOP + j * (HEIGTH_IMG / cells_y), WIDTH_IMG / cells_x, HEIGTH_IMG / cells_y };
			if ((i == cursor_x) && (j == cursor_y))
			{
				rect.x += WIDTH_IMG / cells_x / 20;
				rect.y += HEIGTH_IMG / cells_y / 20;
				rect.w -= WIDTH_IMG / cells_x / 10;
				rect.h -= HEIGTH_IMG / cells_y / 10;
			}
			SDL_RenderCopy(renderer, clip[i][j], NULL, &rect);
		}
	}
}

void Tile::Draw_Win()
{
	string str = "Complited";
	string str_NG = "New Game";
	TTF_Font* font = TTF_OpenFont("19440.ttf", 500);

	SDL_Surface* text = TTF_RenderText_Solid(font, str.c_str(), color_text);
	SDL_Texture* TX_text = SDL_CreateTextureFromSurface(renderer, text);
	if (font == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "TTF Error", SDL_GetError(), window);
		exit(1);
	}
	SDL_Surface* text_NG = TTF_RenderText_Solid(font, str_NG.c_str(), color_text);
	SDL_Texture* TX_text_NG = SDL_CreateTextureFromSurface(renderer, text_NG);

	SDL_Rect rect = { MARGIN_LEFT, MARGIN_TOP, WIDTH_IMG, HEIGTH_IMG };
	SDL_Rect icon_rect = { WIDTH - MARGIN_LEFT - WIDTH_ICON, MARGIN_TOP, WIDTH_ICON, HEIGTH_ICON };
	SDL_Rect rect_text = { 0, 0, WIDTH, MARGIN_TOP };
	SDL_Rect rect_text_NG = { WIDTH - MARGIN_LEFT - WIDTH_ICON, MARGIN_TOP + HEIGTH_IMG - HEIGTH_ICON / 2, WIDTH_ICON, HEIGTH_ICON / 2 };
	SDL_RenderCopy(renderer, Target_IMG, NULL, &rect);
	SDL_RenderCopy(renderer, Target_IMG, NULL, &icon_rect);
	SDL_RenderCopy(renderer, TX_text, NULL, &rect_text);
	SDL_RenderCopy(renderer, TX_text_NG, NULL, &rect_text_NG);

	SDL_FreeSurface(text);
	SDL_DestroyTexture(TX_text);
	SDL_FreeSurface(text_NG);
	SDL_DestroyTexture(TX_text_NG);
}

