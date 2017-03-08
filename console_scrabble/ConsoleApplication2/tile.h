#pragma once
#include <string>
#include "Cellable.h"
// represents a tile
// needs to wrap up both a letter and a score
class Tile : public Cellable
{
public:
	Tile(); //default ctor
	Tile(char a); // ctor with a character

	char letter() const;
	int value() const;

	virtual bool place(Tile* tile) override;
	void multiply_score(int n);
	virtual void print() override;
	virtual char character() override;
	virtual int score() const override;
	Tile& operator=(Tile other);

private:

	int score(char a);
	// returns the score for a certain character
	bool is_in(char letter, std::string str);
	// returns 1 if letter in lowercase is contained in str

	char m_letter;
	int m_score;

};