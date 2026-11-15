#include "board_functionality.h"
#include "game_parameters.h"

using params = GameParameters;

BoardFunctionality::BoardFunctionality() {
	player1BoardCards = {};
	player2BoardCards = {};
}

bool BoardFunctionality::playCard(int playerNumber, Card* card) {
	std::vector<Card*>* cards;

	//Determine which board to add the card to
	if (playerNumber == 1) {
		cards = &player1BoardCards;
	}
	else {
		cards = &player2BoardCards;
	}

	//Check if board size is less than limit
	if (cards->size() < params::boardSize) {
		cards->push_back(card);
		return true;
	}
	
	return false;
}