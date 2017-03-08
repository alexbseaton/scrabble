#include "stdafx.h"
#include "Rack.h"
#include <iostream>
#include <cassert>
Rack::Rack(Bag* bag) : m_length(7)
{
	for (int i = 0; i < m_length; ++i) {
		m_tiles.push_back(bag->draw());
	}
}

bool Rack::is_empty() const
{
	return (!m_length);
}

void Rack::remove(Tile tile)
{
	int pos = where_in_rack(tile.letter());
	// assert that tile is in the rack
	// otherwise we're trying to get
	// a tile we shouldn't be able to
	assert(pos != -1);
	m_tiles.erase(m_tiles.begin()+pos);
	m_length -= 1;
}

void Rack::remove(char ch)
{
	int pos = where_in_rack(ch);
	// assert that tile is in the rack
	assert(pos != -1);
	m_tiles.erase(m_tiles.begin() + pos);
	m_length -= 1;
}

void Rack::print() const
{
	for (auto t : m_tiles) {
		t.print();
		std::cout << " ";
	}
}

void Rack::add(Tile tile)
{
	// you are never allowed more than 7 tiles
	assert(m_tiles.size() < 7);
	m_tiles.push_back(tile);
	m_length += 1;
}

void Rack::add(char letter)
{
	// you are never allowed more than 7 tiles
	assert(m_tiles.size() < 7);
	Tile tile(letter);
	m_tiles.push_back(tile);
	m_length += 1;
}

bool Rack::contains(char ch) const
{
	for (auto tile : m_tiles) {
		if (tile.letter() == ch) return true;
	}
	return false;
}

int Rack::where_in_rack(char letter) const
{
	// if two tiles the same are in the rack,
	// just return the position of the first one.
	for (int i = 0; i < m_length; ++i) {
		if (m_tiles[i].letter() == letter) return i;
	}

	return -1;
}