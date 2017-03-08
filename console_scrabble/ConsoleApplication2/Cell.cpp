#include "stdafx.h"
#include "Cell.h"
#include "tile.h"

Cell::Cell() : m_contents(new Tile('z'))
{

}

Cell::Cell(Cellable* cellable) : m_contents(cellable)
{

}

void Cell::setup_with(Cellable* cellable)
{
	m_contents = cellable;
}

void Cell::place(Tile* tile)
{
	if (m_contents->place(tile)) { m_contents = tile; };
}

void Cell::place(char ch)
{
	Tile* tile = new Tile(ch);
	if (m_contents->place(tile)) { m_contents = tile; };
}

bool Cell::try_to_place(char ch)
{
	// this is '0' if m_contents isn't a tile
	char letter = m_contents->character();
	if (letter == '0' ||
		letter == ch) {
		return true;
	}
	return false;
}

bool Cell::is_empty() const
{
	// this is '0' is m_contents isn't a tile
	char letter = m_contents->character();
	if (letter == '0') return true;
	return false;
}


void Cell::print()
{
	m_contents->print();
}

int Cell::score() const
{
	return m_contents->score();
}

char Cell::character() const
{
	return m_contents->character();
}

Cell& Cell::operator=(Cell other)
{
	m_contents = other.m_contents;
	return *this;
}

void Cell::delete_contents()
{
	if (m_contents) delete m_contents;
}

Cell::~Cell()
{

}