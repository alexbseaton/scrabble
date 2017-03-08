#pragma once
#include "stdafx.h"
#include "Empty.h"
#include "tile.h"
#include <iostream>

bool Empty::place(Tile* tile)
{
	// nothing to do
	// it's always fine to put a tile on an empty square
	return true;
}

void Empty::print()
{
	std::cout << "[]";
}