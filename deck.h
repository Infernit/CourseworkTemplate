#pragma once
#include "suit.h"
#include "card.h"

class Deck {
public:
	Deck(int value);
	int getCardCount();
	std::vector<Card> getCards();
	Card drawNextCard();
	void shuffleDeck();
	

private:
	std::vector<Card> _cards;
	std::vector<Suit> _suits;
	void populateDeck();
	void populateSuits();

};