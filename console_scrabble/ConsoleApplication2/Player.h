#pragma once

#include <string>
#include "Rack.h"
#include "board.h"
#include "Bag.h"

class Player
{
public:
	// Ctor. Draws the tiles for Player from  Bag.
	Player(
		const std::string name, 
		Board* board,
		Bag* bag
		);

	void set_next(Player* player);

	bool first_turn();

	bool start_turn();

	// Put tile at (row, column) on m_board
	void place(Tile tile, int row, int column);

	// Usually passes responsibility on to the next player
	// unless the game is over
	void end_turn();

	std::string name() const;

	int score() const;

	~Player();

private:

	// direction == 1 is across, -1 is down
	bool get_data(
		std::string& str,
		int& row,
		int& column,
		int& direction
		);

	// Prints the board and the rack
	void display_data();

	// Checks whether a string is valid and makes it lowercase
	bool is_valid(std::string& str);

	// Put str down starting at (row, column) in direction
	bool play(
		std::string& str, 
		int row, 
		int column, 
		int direction
		);

	Rack m_rack;
	int m_score;
	std::string m_name;
	Board* const m_board;
	Player* m_next_player;
	Bag* const m_bag;


};