#include "stdafx.h"

#include "Word.h"
#include <fstream>
#include <cassert>

using namespace std;

Word::Word() : m_string("")
{

}

Word::Word(string str) : m_string(str)
{

}

void Word::add_letter(char ch)
{
	m_string += ch;
}

bool Word::is_english()
{
	string line;
	ifstream words ("words.txt");
	// open words
	assert(words.is_open() && "could not open words file");

	// This way of checking is very slow,
	// because it doesn't exploit the fact that words
	// is ordered alphabetically. Could do eg binary
	// search through words for line if this becomes
	// a problem.
	while (getline(words, line)) {
		if (line == m_string) {
			words.close();
			return true;
		}
	}
	
	words.close();
	return false;
}
