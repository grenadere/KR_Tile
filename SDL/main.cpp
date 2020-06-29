#include "Tile.h"

using namespace std;

int SDL_main(int argc, char* argv[])
{
	Tile Game;
	SDL_Event e;
	int quit = 0;
	while (!quit) {
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_MOUSEBUTTONDOWN:
				Game.Button_Click(e.motion.x, e.motion.y);
				break;
			case SDL_MOUSEMOTION:
				Game.Button_Mov(e.motion.x, e.motion.y);
				break;

			case SDL_KEYUP:
				if (e.key.keysym.sym == SDLK_ESCAPE)
					quit = true;
				break;
			case SDL_QUIT:
					quit = true;
					break;
			}
			Game.Draw();
		}
		
	}
	return 0;
}