#pragma once
#include "game_parameters.h"

class Deck {
public:
	Deck();
	int getCardCount();
	std::vector<Card> getCards();
	Card drawNextCard();
	void shuffleDeck();
	std::string toString();
	

private:
	std::vector<Card> _cards;
	std::vector<Suit> _suits;
	void populateDeck();
	void populateSuits();

};