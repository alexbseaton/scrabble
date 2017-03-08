#pragma once
#include <string>

// Class that has responsibility for checking
// whether a sequence of tiles is indeed a
// dictionary word.

class Word
{
public:
	Word();
	Word(std::string str);

	// append ch to m_string
	void add_letter(char ch);
	// checks if Word is in the scrabble dictionary
	bool is_english();
private:
	// the string representing Word
	std::string m_string;
};
