#pragma once
#include "stdafx.h"
#include "matrix.h"
#include "Cell.h"
#include <string>
#include <vector>

class Board
{
public:
// Methods
	Board(int rows, int columns);
	Board(); //makes us a 2x2 board for testing

	void print(); //output contents of the board to console

	// Query get methods for the size of board
	int no_rows() const;
	int no_columns() const;

	void place(int row, int column, Tile tile);
	// PLayers might need to know about Boards

	// Returns a vector of characters we need to play the
	// provided turn
	std::vector<char> needed(
		std::string str, 
		int row, 
		int column, 
		int direction
		) const;

	// Try to put str down, starting at (row,column)
	// Return true if it is possible to do this
	// needs modifying to check that auxillary words are english
	bool attempt(std::string str, 
		int row, 
		int column, 
		int direction
		);

	// Put str down on the board and return the score for
	// the turn
	// PRECONDITION: Must have invoked attempt(...) first
	bool put_down(
		std::string str,
		int row,
		int column,
		int direction,
		int& d_score
		);

	// checks that words made NOT IN DIRECTION are english
	// can assume everything fits,
	// PRECONDITION: attempt(...) has been invoked
	// direction is 1 for across and -1 for down
	bool check_other_words(
		std::string str, 
		int row, 
		int column, 
		int direction
		);

	// just lifted from player, needs refactoring
	bool is_valid(std::string& str);

	// Responsible for deleting the dynamically allocated
	// cell contents constructed in Board's ctor
	~Board();

// Data
private:

	//15*15 matrix for the board
	Matrix<Cell> m_cells; 
	int m_rows;
	int m_columns;

	// Helper fns

	// Checks that the word formed above/across
	// of the tile at (row, column) is valid
	bool check_above(int row, int column, char player_letter);
	bool check_across(int row, int column, char player_letter);
	// return how many extra points we are owed for words
	// made at right angles to our 'main word'
	int points_above(int row, int column) const;
	int points_across(int row, int column) const;
	// does cell at (row, column) have a neighbour
	// above or below it?
	bool has_neighbour_up(int row, int column) const;
	bool has_neighbour_across(int row, int column) const;
	// how far above/below (row, column) does an unbroken
	// line of tiles stretch?
	int highest_above(int row, int column) const;
	int lowest_below(int row, int column) const;
	// how far left/right of (row, column) does an unbroken
	// line of tiles stretch?
	int furthest_right(int row, int column) const;
	int furthest_left(int row, int column) const;
	// does (row, column) have a Tile up down left or right of it?
	bool has_neighbour(int row, int column) const;
};
