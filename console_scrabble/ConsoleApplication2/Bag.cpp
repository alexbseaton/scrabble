#include "stdafx.h"
#include "Bag.h"
#include <cstdlib>
#include <time.h>

Bag::Bag()
{
	add("kjxqz", 1);
	add("bcmpfhvwy", 2);
	add("g", 3);
	add("lsud", 4);
	add("nrt", 6);
	add("o", 8);
	add("ai", 9);
	add("e", 12);
}

void Bag::add(std::string str, int n)
{
	for (int i = 0; i < n; ++i) {
		for (char c : str) {
			m_letters.push_back(c);
		}
	}
}

bool Bag::is_empty() const
{
	return m_letters.empty();
}

char Bag::draw()
{
	int length = m_letters.size();

	// get a random index between 0 and length-1
	std::srand(time(NULL));
	int index = std::rand() % length;

	// erase the corresponding letter from m_letters
	char letter = m_letters[index];
	m_letters.erase(m_letters.begin() + index);
	return letter;
}

Bag::~Bag()
{
	// nothing to do here
}