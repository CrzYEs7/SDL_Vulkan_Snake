#ifndef CELL_H
#define CELL_H

#include "globals.h"

struct Cell
{
	int size;
	int x = -1 * SCREEN_SIZE;
	int y = -1 * SCREEN_SIZE;
	Uint32 color;
};

#endif
