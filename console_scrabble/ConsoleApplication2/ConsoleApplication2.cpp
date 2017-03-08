// Task: Make a scrabble game!!

#include "stdafx.h"
#include "board.h"
#include "Rack.h"
#include "Word.h"
#include <iostream>
#include <string>
#include "board.h"
#include "Player.h"
#include "Bag.h"

int main()
{
	Board board(10,10);
	Bag bag;
	Player alex("Alex", &board, &bag);
	Player bill("Angela", &board, &bag);
	alex.set_next(&bill);
	bill.set_next(&alex);

	while (true) {
		if (alex.first_turn()) break;
	}

	std::cout << "Game over!! \n The scores are:\n" <<
		alex.name() << "\t" << alex.score() << "\n"
		<< bill.name() << "\t" << bill.score() << "\n";
	std::string winner{ bill.name()};
	if (alex.score() > bill.score()) winner = alex.name();

	std::cout << "The winner is " << winner << 
		". Congratulations!\n Enter any key to leave. ";


	
	//keep window open
	char a;
	std::cin >> a;
    return 0;
}

