#pragma once
#include "suit.h"

class Card {

public:
	Card();
	Card(Suit suit, int rank);
	std::vector<Effect> getCardEffects();
	Suit getCardSuit();
	int getCardRank();
	std::string toString();

protected:
	Suit _cardSuit;
	int _cardRank;
	std::vector<Effect> _cardEffects;


private:


};
