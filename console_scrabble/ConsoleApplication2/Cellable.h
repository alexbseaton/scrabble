#pragma once
// ABC for Empty, Bonus, Tile
// Cellable meaning "Stuff we can put in a Cell"
class Tile;

class Cellable
{
public:
	// invoked when a tile is place on the Cellable
	virtual bool place(Tile* tile) = 0;

	//returns the character associated with the tile,
	// or '0' if not a tile
	virtual char character();
	virtual int score() const;

	//virtual void multiply_score(int n);
	virtual void print() = 0;
private:
};