#pragma once
#include "suit.h"
#include "card.h"
#include <vector>
#include <string>

class Deck {
public:
	Deck();
	int getCardCount();
	std::vector<Card> getCards();
	std::vector<Card> getDrawnCards();
	Card drawNextCard();
	void shuffleDeck();
	void setMaxEnergy(int value);
	std::string toString();
	

private:
	std::vector<Card> _cards;
	std::vector<Card> _drawnCards;
	std::vector<Suit> _suits;
	void populateDeck(int energyLimit);
	void populateSuits();
};