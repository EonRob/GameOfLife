#include <iostream>
#include <vector>
//#include <SDL.h>

#include "Cronway.h"

	Cronway::Cronway(float p_boardSize, int p_def)
		:boardSize(p_boardSize), def(p_def)
	{
		cellSize = boardSize / (float) def;

		backgroundRect.x = 0;
		backgroundRect.y = 0;
		backgroundRect.w = boardSize;
		backgroundRect.h = boardSize;

		loop = 0;
		totalValues = (def * def);
		data = new bool[totalValues*2];
	}

	void Cronway::draw(SDL_Renderer* renderer)
	{
		// Draw background

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRectF(renderer, &backgroundRect);

		// Iterate through data array and draw active cells

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		for (int j = 0; j < def; ++j)
		{
			for (int i = 0; i < def; ++i)
			{
				if (data[(j * def) + i + loop * totalValues])
				{
					SDL_FRect rect;
					rect.x = i * cellSize;
					rect.y = j * cellSize;
					rect.w = cellSize;
					rect.h = cellSize;
					SDL_RenderFillRectF(renderer, &rect);
				}
			}
		}
	}

	void Cronway::randomize()
	{
		// This function goes through the data array and randomize values

		for (int i = 0; i < totalValues; ++i)
		{
			if (randomNumber(0,2) == 0)
				data[i] = false;
			else
				data[i] = true;
		}
	}

	void Cronway::update()
	{
		for (int j = 0; j < def; ++j)
		{
			for (int i = 0; i < def; ++i)
			{
				// Get "c" value that represent the position of current cell in the array

				int c = (j * def) + i;

				// Count the number of active surrounding cells for the current loop frame

				int count = 0;
				//   \ | /		
				//   -   -
				//   / | \   
				if (data[(totalValues + c - def - 1) % totalValues + loop * totalValues])
					count += 1;
				if (data[(totalValues + c - def) % totalValues + loop * totalValues])
					count += 1;
				if (data[(totalValues + c - def + 1) % totalValues + loop * totalValues])
					count += 1;
				if (data[(totalValues + c - 1) % totalValues + loop * totalValues])
					count += 1;
				if (data[(totalValues + c + 1) % totalValues + loop * totalValues])
					count += 1;
				if (data[(totalValues + c + def - 1) % totalValues + loop * totalValues])
					count += 1;
				if (data[(totalValues + c + def) % totalValues + loop * totalValues])
					count += 1;
				if (data[(totalValues + c + def + 1) % totalValues + loop * totalValues])
					count += 1;

				// Default rule to apply, check current cell status and apply to next step

				if (data[c + loop * totalValues] && (count == 2 | count == 3))
					data[c + ((loop + 1) % 2) * totalValues] = true;
				else if (!data[c + loop * totalValues] && count == 3)
					data[c + ((loop + 1) % 2) * totalValues] = true;
				else if (count == 2)
					data[c + ((loop + 1) % 2) * totalValues] = data[c + loop * totalValues];
				else
					data[c + ((loop + 1) % 2) * totalValues] = false;
			}
		}
		// Update loop position

		loop = (loop + 1) % 2;
	}