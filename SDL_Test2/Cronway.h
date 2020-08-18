#pragma once
#include <SDL.h>

#include "Utils.h"

class Cronway
{
private:
	int def;
	bool *data;
	int totalValues;
	int loop;
	float boardSize;
	float cellSize;
	SDL_FRect backgroundRect;

public:
	Cronway(float p_boardSize, int p_def);
	void draw(SDL_Renderer *renderer);
	void randomize();
	void update();
};