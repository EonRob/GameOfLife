#include <iostream>
#include <SDL.h>

#include "Utils.h"
#include "Cronway.h"

static const int width = 720;
static const int height = 720;

int main(int argc, char* args[])
{
	int currentTime = 0;
	float deltaTime = 0.0f;

	float fps = 30.0f;
	float frameTime = 1000.0f / fps;

	Cronway cronway(720, 180);
	cronway.randomize();


	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	
	bool running = true;

	SDL_Event ev;
	while (running)
	{
		currentTime = SDL_GetTicks();

		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
				running = false;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Draw

		cronway.draw(renderer);

		SDL_RenderPresent(renderer);

		//Update

		cronway.update();

		// Limit FPS - wait if frame time isn't reached

		deltaTime = SDL_GetTicks() - currentTime;
		if (deltaTime < frameTime)
			SDL_Delay(frameTime - deltaTime);
	}

	

	// Release ressources
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

