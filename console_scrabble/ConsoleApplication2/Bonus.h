#pragma once
#include "Cellable.h"
// Represents a Bonus tile like double letter, triple word
// Just does double/triple letter for now


class Bonus : public Cellable
{
public:
	Bonus(int multiplier); // ctor with multiplier,
	// which will be either 2 or 3 for double or
	// triple letter.

	virtual bool place(Tile* tile) override;
	virtual void print() override;

private:
	int m_multiplier;
};