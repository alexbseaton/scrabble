#pragma once
#include "Cellable.h"
// Represents an empty tile (no bonus or tile on it)

class Empty : public Cellable
{
public:
	virtual bool place(Tile* tile) override;
	virtual void print() override;
private:
	
};