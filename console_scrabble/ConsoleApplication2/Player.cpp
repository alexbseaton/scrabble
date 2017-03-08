#include "stdafx.h"
#include "Player.h"
#include "Word.h"
#include <iostream>
#include <cctype>

using namespace std;

Player::Player(
	const string name,
	Board* board,
	Bag* bag
	) : m_name(name), 
	m_board(board),
	m_score(0),
	m_rack(bag),
	m_bag(bag),
	m_next_player(NULL)
{
	// nothing to do here
}

void Player::set_next(Player* player)
{
	m_next_player = player;
}

bool Player::get_data(
	std::string& str,
	int& row,
	int& column,
	int& direction
	)
{
	// ROWS
	cout << "Which row do you want to start in? ";
	if (!(cin >> row)) {
		cout << "Row invalid " << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}
	// check row lies in proper range
	if ((row > m_board->no_rows()) ||
		(row < 1)
		) {
		cout << "Row out of range " << endl;
		return false;
	}

	// COLUMNS
	cout << "Which column?";
	if (!(cin >> column)) {
		cout << "Column invalid " << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}
	// check column lies in proper range
	if ((column > m_board->no_rows()) ||
		(column < 1)
		) {
		cout << "Column invalid. " << endl;
		return false;
	}

	// DIRECTION
	cout << "Play across or down from there?"
		<< "\nEnter a for across or d for down";
	char c;
	if (!(cin >> c)) {
		cout << "Direction invalid " << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}
	if (c == 'a') {
		direction = 1;
	}
	else if (c == 'd') {
		direction = -1;
	}
	else {
		cout << "Direction was not a or d." << endl;
		return false;
	}

	// THE WORD
	cout << "What word do you want to play? ";
	if (!(cin >> str)) {
		cout << "Input invalid " << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}
	// Check that the word entered is in the list,
	// is alphabetic, and put it in to lower case
	if (!is_valid(str)) {
		cout << "Word was not valid." << endl;
		return false;
	}
	return true;
}

bool Player::play(
	std::string& str,
	int row,
	int column,
	int direction
	)
{
	auto needed_letters =
		m_board->needed(str, row, column, direction);
	// check that rack has these letters then
	// remove them from rack
	int number_taken = 0;
	for (char letter : needed_letters) {
		if (!m_rack.contains(letter)) {
			cout << "Rack doesn't have all the letters needed"
				<< endl;
			return false;
		}
		number_taken += 1;
		m_rack.remove(letter);
	}

	// Modify the score and put the necessary tiles down
	int d_score = 0;
	if (!m_board->
		put_down(str, row, column, direction, d_score)) {
		return false;
	}
	m_score += d_score;

	// Draw next tiles
	for (int i = 0; i < number_taken; ++i) {
		if (!m_bag->is_empty()) {
			m_rack.add(m_bag->draw());
		}
	}
	return true;
}

bool Player::first_turn()
{
	cout << "Welcome to the word game. It is " << m_name <<
		"'s turn.\n";

	int row, column, direction;
	string str;
	display_data();

	// Ask player for a word, row, column and direction
	if (!get_data(str, row, column, direction)) return false;

	// Check that it fits
	if (direction == 1 &&
		row + str.length()-1 > m_board->no_rows()) {
		cout << "Word too long. ";
		return false;
	}
	if (direction == -1 &&
		column + str.length()-1 > m_board->no_columns()) {
		cout << "Word too long. ";
		return false;
	}

	play(str, row, column, direction);

	end_turn();

	return true;
}

bool Player::start_turn()
{
	cout << "It is " << m_name << "'s turn.\n";
	char c;
	cout << "Enter 0 to end, anything else to continue. ";
	cin >> c;
	if (c == '0') return true;

	int row, column, direction;
	string str;
	display_data();

	// Ask player for a word, row, column and direction
	if (!get_data(str, row, column, direction)) return false;

	// now ask the board to try putting str down
	if (!m_board->attempt(str, row, column, direction)) {
		cout << "Word doesn't fit on the board properly" 
			<< endl;
		return false;
	}
	
	// put the tiles down
	if(!play(str, row, column, direction)) return false;

	end_turn();

	return true;
}

void Player::end_turn()
{
	cout << m_name << ", your turn is over. " << endl;
	cout << "Your score is: " << m_score << "\n\n";

	while (true) {
		if (m_next_player->start_turn()) break;
	}
}

void Player::display_data()
{
	cout << "The board is: " << endl;
	m_board->print();
	cout << '\n';
	cout << "The rack is: " << endl;
	m_rack.print();
	cout << '\n';
}

bool Player::is_valid(string& str)
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

void Player::place(Tile tile, int row, int column)
{
	m_rack.remove(tile);
	m_board->place(row, column, tile);
}

std::string Player::name() const
{
	return m_name;
}

int Player::score() const
{
	return m_score;
}

Player::~Player()
{
	// nothing to do here
}