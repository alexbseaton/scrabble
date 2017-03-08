#include "stdafx.h"
#include "board.h"
#include "Bonus.h"
#include "tile.h"
#include "Empty.h"
#include "Word.h"
#include <iostream>
#include <memory>
#include <cassert>
// Responsible for storing the configuration of the board

Board::Board(int rows, int columns)
	: m_cells(rows, columns), 
	m_rows (rows), 
	m_columns (columns)
{
	for (int row = 1; row <= m_rows; ++row) {
		for (int column = 1; column <= m_columns; ++column) {
			auto cellable = new Empty; // deleted in destructor
			m_cells(row, column).setup_with(cellable);
		}
	}
}

Board::Board()
	: m_cells(3, 3), m_rows(3), m_columns(3)
{
	for (int row = 1; row <= m_rows; ++row) {
		for (int column = 1; column <= m_columns; ++column) {
			auto cellable = new Empty; // deleted in destructor
			m_cells(row, column).setup_with(cellable);
		}
	}

}

int Board::no_rows() const
{
	return m_rows;
}

int Board::no_columns() const
{
	return m_columns;
}

void Board::print()
{
	for (int row = 1; row <= m_rows; ++row) {
		std::cout << '\n';
		for (int col = 1; col <= m_columns; ++col) {
			m_cells(row, col).print();
			std::cout << "  ";
		}
	}

}

void Board::place(int row, int column, Tile tile)
{
	m_cells(row, column).place(&tile);
}

// direction is 1 for across and -1 for down
bool Board::attempt(
	std::string str, 
	int row, 
	int column,
	int direction)
{
	// check what we're putting doesn't overflow the board
	// The -1 arises because we are counting from 0
	int length = str.length();
	if (
		((direction == 1) && (column + length - 1 > m_columns)) 
		||
		((direction == -1) && (row + length - 1 > m_rows))
		) {
		// word too long
		return false;
	}

	// check that if the words uses pre-existing
	// tiles then they are the right character.
	// Also check that the word touches stuff already
	// on the board (crossword style).
	bool isolated = true; //does the turn touch no other tiles?
	if (direction == 1) {
		for (int i = 0; i < length; ++i) {
			Cell* cell = &m_cells(row, column + i);
			if (!cell->try_to_place(str[i])) return false;
			if (has_neighbour(row, column + i)) isolated = false;
		}
	}
	if (direction == -1) {
		for (int i = 0; i < length; ++i) {
			Cell* cell = &m_cells(row + i, column);
			if (!cell->try_to_place(str[i])) return false;
			if (has_neighbour(row+i, column)) isolated = false;
		}
	}

	if (isolated) {
		std::cout << "Trying to play standalone word. ";
		return false;
	}

	// Check that any auxillary words we create are english
	return check_other_words(str, row, column, direction);
}

// Check that words made in our turn other than str
// are valid
bool Board::check_other_words(
	std::string str,
	int row,
	int column,
	int direction
	)
{
	int length = str.length();
	// for each letter in str, check that words at right angles
	// to direction are valid
	for (int i = 0; i < length; ++i) {
		// if we're playing across
		if (direction == 1) {
			return check_above(row, column + i, str[i]);
		}

		// if we're playing up/down
		if (direction == -1) {
			return check_across(row + i, column, str[i]);
		}
	}
	return true;
}

bool Board::check_across(int row, int column, char player_letter)
{
	// cell may not have anything left or right of it,
	// in which case we needn't do anything
	if (!has_neighbour_across(row, column)) return true;

	// check word formed left/right of cell
	Cell* cell = &m_cells(row, column);
	Cell* cell_temp = cell;
	std::string result = "";

	// find how far right the word goes
	int max_col = furthest_right(row, column);

	// find how far left the word goes
	int min_col = furthest_left(row, column);


	// check the word spanned by tiles from min to max col
	int col_temp = min_col;
	while (col_temp < column) {
		char c = m_cells(row, col_temp).character();
		result += c;
		++col_temp;
	}
	result += player_letter;
	col_temp = column + 1;
	while (col_temp <= max_col) {
		char c = m_cells(row, col_temp).character();
		result += c;
		++col_temp;
	}
	if (!is_valid(result)) {
		std::cout <<
			"\nPlaying this turn creates illegal words."
			<< std::endl;
		return false;
	}
	return true;
}

bool Board::check_above(int row, int column, char player_letter)
{
	
	// cell may not have anything above or below it,
	// in which case we return true
	if (!has_neighbour_up(row, column)) return true;

	// check word formed up/down of cell
	Cell* cell = &m_cells(row, column);
	Cell* cell_temp = cell;
	std::string result = "";

	// find how low the word goes
	int max_row = lowest_below(row, column);

	// find how high the word goes
	int min_row = highest_above(row, column);	


	// check the word spanned by tiles from min to max row
	int row_temp = min_row;
	while (row_temp < row) {
		char c = m_cells(row_temp, column).character();
		result += c;
		++row_temp;
	}
	result += player_letter;
	row_temp = row + 1;
	while (row_temp <= max_row) {
		char c = m_cells(row_temp, column).character();
		result += c;
		++row_temp;
	}
	if (!is_valid(result)) {
		std::cout <<
			"\nPlaying this turn creates illegal words."
			<< std::endl;
		return false;
	}
	return true;
}

// this is just lifted from player, needs refactoring somehow
bool Board::is_valid(std::string& str)
{
	for (char& c : str) {
		if (!isalpha(c)) return false;
		char lowered = tolower(c);
		c = lowered;
	}
	Word word(str);
	if (!word.is_english()) return false;

	return true;

}

std::vector<char> Board::needed(
	std::string str,
	int row,
	int column,
	int direction
	) const
	//Direction is 1 for across and -1 for down
{
	std::vector<char> result;
	int length = str.length();

	Cell* cell = NULL;
	for (int i = 0; i < length; ++i) {
		if (direction == 1) { 
			cell = &m_cells(row, column + i); 
		}
		else if (direction == -1) {
			cell = &m_cells(row + i, column);
		}

		if (cell->is_empty()) result.push_back(str[i]);
	}

	return result;
}

// Needs modifying so that we also get points for the
// 'auxillary' words we create
bool Board::put_down(
	std::string str,
	int row,
	int column,
	int direction,
	int& d_score
	)
{
	int result = 0;
	int length = str.length();

	// for each letter in str
	for (int i = 0; i < length; ++i) {
		Cell* cell = NULL;
		// if we're going across
		if (direction == 1) {
			cell = &m_cells(row, column + i);
			if (cell->is_empty()) {
				cell->place(str[i]);
				result += points_above(row, column + i);
			}
			
		}
		// if we're going up/down
		else if (direction == -1) {
			cell = &m_cells(row + i, column);
			if (cell->is_empty()) {
				cell->place(str[i]);
				result += points_across(row + i, column);
			}
			
		}

		result += cell->score();
	}
	d_score += result;
	return true;
}

int Board::highest_above(int row, int column) const
{
	int min_row = row;
	while (min_row > 1) {
		Cell* cell = &m_cells(min_row - 1, column);
		if (cell->is_empty()) break;
		--min_row;
	}
	return min_row;
}

int Board::lowest_below(int row, int column) const
{
	int max_row = row;
	while (max_row < m_rows) {
		Cell* cell_temp = &m_cells(max_row + 1, column);
		if (cell_temp->is_empty()) break;
		++max_row;
	}
	return max_row;
}

int Board::furthest_left(int row, int column) const
{
	int min_col = column;
	while (min_col > 1) {
		Cell* cell = &m_cells(row, min_col - 1);
		if (cell->is_empty()) break;
		--min_col;
	}
	return min_col;
}

int Board::furthest_right(int row, int column) const
{
	int max_col = column;
	while (max_col < m_columns) {
		Cell* cell = &m_cells(row, max_col + 1);
		if (cell->is_empty()) break;
		++max_col;
	}
	return max_col;
}

bool Board::has_neighbour(int row, int column) const
{
	return (
		has_neighbour_up(row, column)
		|| has_neighbour_across(row, column)
		);
}

bool Board::has_neighbour_up(int row, int column) const
{
	bool is_alone = false;
	bool anything_above = false;
	bool anything_below = false;
	// check above
	Cell* cell_t = NULL;
	if (row < m_rows) {
		cell_t = &m_cells(row + 1, column);
		if (!cell_t->is_empty()) anything_above = true;
	}
	// check below
	if (row > 1) {
		cell_t = &m_cells(row - 1, column);
		if (!cell_t->is_empty()) anything_below = true;
	}
	// if tile is alone, there is no more to do
	is_alone = (!anything_below) && (!anything_above);
	return !is_alone;
}

bool Board::has_neighbour_across(int row, int column) const
{
	bool is_alone = false;
	bool anything_right = false;
	bool anything_left = false;
	// check right
	Cell* cell_t = NULL;
	if (column < m_columns) {
		cell_t = &m_cells(row, column + 1);
		if (!cell_t->is_empty()) anything_right = true;
	}
	// check left
	if (column > 1) {
		cell_t = &m_cells(row, column - 1);
		if (!cell_t->is_empty()) anything_left = true;
	}
	// if tile is alone, there is no more to do
	is_alone = (!anything_left) && (!anything_right);
	return !is_alone;
}

int Board::points_above(int row, int column) const
{
	// is there anything above/below?
	if (!has_neighbour_up(row, column)) return 0;

	// so it does have something above/below
	int min_row = highest_above(row, column);
	int max_row = lowest_below(row, column);

	int result = 0;
	// add a score for each tile
	for (int i = min_row; i <= max_row; ++i) {
		Cell* cell = &m_cells(i, column);
		result += cell->score();
	}
	return result;
}

int Board::points_across(int row, int column) const
{
	// is there anything left/right?
	if (!has_neighbour_across(row, column)) return 0;

	// so it does have something left/right
	int min_col = furthest_left(row, column);
	int max_col = furthest_right(row, column);

	int result = 0;
	// add a score for each tile
	for (int i = min_col; i <= max_col; ++i) {
		Cell* cell = &m_cells(row, i);
		result += cell->score();
	}
	return result;
}

Board::~Board()
{
	for (int row = 1; row <= m_rows; ++row) {
		for (int column = 1; column <= m_columns; ++column) {
			m_cells(row, column).delete_contents();
		}
	}
}