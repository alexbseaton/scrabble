#include "stdafx.h"
#include "Bonus.h"
#include "tile.h"
#include <cassert>
#include <iostream>


Bonus::Bonus(int multiplier) : m_multiplier(multiplier)
{
	// Multiplier can only be 2 or 3 in Scrabble
	assert((multiplier == 2) || (multiplier == 3));
}

bool Bonus::place(Tile* tile)
{
	tile->multiply_score(m_multiplier);
	return true;
}

void Bonus::print()
{
	std::cout << "X" << m_multiplier;
}