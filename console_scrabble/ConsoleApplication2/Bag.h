#pragma once
#include <vector>
#include <string>
// Represents a bag of letters that players can draw from

class Bag
{
public:

	// Puts the english letter distr. in m_letters
	Bag();

	bool is_empty() const;

	char draw(); // the letter we take from the bag

	~Bag();
private:
	std::vector<char> m_letters; // the letters in the bag

	// puts each char in str in m_letters.
	// Only needs to be used in ctor
	void add(std::string str, int n); 
};