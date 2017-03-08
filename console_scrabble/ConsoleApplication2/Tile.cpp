#include "stdafx.h"
#include "tile.h"
#include <ctype.h>
#include <string>
#include <cassert>
#include <iostream>

bool Tile::place(Tile* tile)
{
	std::cout << "ERROR. TRYING TO PUT A TILE ON ANOTHER. ";
	return false;
}

void Tile::print()
{
	std::cout << char(toupper(m_letter)) << m_score;
}

void Tile::multiply_score(int n) 
{
	m_score *= n;
}

char Tile::letter() const
{
	return m_letter;
}

int Tile::value() const
{
	return m_score;
}

char Tile::character()
{
	return letter();
}

bool Tile::is_in(char a, std::string str) {
	char letter = tolower(a);
	std::size_t found = str.find(letter);
	if (found != std::string::npos)	
		return true;
	return false;
}

int Tile::score(char a) {
	// if a isn't alphabetic we're in trouble...
	std::string str = "abcdefghijklmnopqrstuvwxyz";
	assert(is_in(a, str));
	// if letter in 'aeioulnstr' return 1
	str = "aeioulnstr";
	if (is_in(a, str)) return 1;
	// if letter in 'dg' return 2
	str = "dg";
	if (is_in(a, str)) return 2;
	// 'bcmp' return 3
	str = "bcmp";
	if (is_in(a, str)) return 3;
	// 'fhvwy' return 4
	str = "fhvwy";
	if (is_in(a, str)) return 4;
	// 'k' return 5
	str = "k";
	if (is_in(a, str)) return 5;
	// 'jx' return 8
	str = "jx";
	if (is_in(a, str)) return 8;
	// 'qz' return 10
	str = "qz";
	if (is_in(a, str)) return 10;

	assert(1 == 0); //we should never get down here

	return -1;


}

Tile::Tile()
	: m_letter('a'), m_score(0)
{
	m_score = score(m_letter);
}

Tile::Tile(char a)
	: m_letter(a)
{
	m_score = score(a);
}

Tile& Tile::operator=(Tile other) 
{
	m_letter = other.m_letter;
	m_score = other.m_score;
	return *this;
}

int Tile::score() const
{
	return m_score;
}
 