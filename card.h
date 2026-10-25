#pragma once
#include "suit.h"

class Card {

public:
	Card(Suit suit, int rank);
	std::vector<Effect> getCardEffects();

protected:
	Suit cardSuit;
	int cardRank;
	std::vector<Effect> cardEffects;


private:


};
