#pragma once
#include "tile.h"
#include "Bag.h"
#include <vector>
class Rack
{
public:
	// For testing, constructs to 'AAAAAAP'
	// When Bag is done we can use that, Rack(Bag)
	// No!! Just do Rack(Tile)
	Rack(Bag* bag);

	// Takes Tile from the rack
	// Asserts tile is in rack
	void remove(Tile tile); //might not need this one
	void remove(char ch);

	// Adds a tile to the rack.
	// Checks rack is a suitable length
	void add(Tile tile); //might not need this one
	void add(char ch);

	// Checks if a Tile with character ch is in Rack
	bool contains(char ch) const;

	//
	bool is_empty() const;

	// Prints the contents of the rack
	void print() const;

private:

	// returns index of first occurence of tile in rack
	// or -1 if tile is not in rack
	int where_in_rack(char letter) const;

	std::vector<Tile> m_tiles;
	int m_length;



};