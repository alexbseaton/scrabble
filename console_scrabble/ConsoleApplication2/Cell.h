#pragma once
#include "Cellable.h"
#include "tile.h"
#include <memory>
// Cell on the board.
// Contains either:
// i) Empty ii) Bonus iii) Tile
// all of which are derived from Cellable

class Cell
{
public:
	Cell();
	//Put cellable in the cell
	Cell(Cellable* cellable);
	// Put tile in the cell
	void place(Tile* tile); 
	// Put a tile with character ch inside cell
	void place(char ch);

	// returns 0 if the cell doesn't have a tile
	int score() const;
	// returns the character associated with the tile in the 
	// cell, or '0' if not a tile
	char character() const;

	// return
	bool try_to_place(char ch);

	// does the cell have a tile in it?
	bool is_empty() const;

	void print(); //invokes m_contents->print()
	void setup_with(Cellable* cellable);

	Cell& operator=(Cell other);

	void delete_contents();

	~Cell();
private:
	Cellable* m_contents;
};