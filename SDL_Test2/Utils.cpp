#include <stdlib.h>
#include "time.h"

// Generate random number with min and max
int randomNumber(int nr_min, int nr_max)
{
	// init with current time, make sure it init only once
	static bool initialized = false;
	if (!initialized)
	{
		initialized = true;
		srand(time(NULL));
	}
	// Generate the random number
	return rand() % nr_max + nr_min;
}

int randomColor()
{
	return randomNumber(0, 255);
}