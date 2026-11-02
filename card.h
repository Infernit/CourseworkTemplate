#pragma once
#include "suit.h"
#include <vector>

class Card {

public:
	Card();
	Card(Suit suit, int rank);
	std::vector<Effect> getCardEffects();
	Suit getCardSuit();
	int getCardRank();
	// Receive this information too
	bool getIsRoyal();
	std::string toString();

protected:
	Suit _cardSuit;
	int _cardRank;
	std::vector<Effect> _cardEffects;
	// If it has rank 11 (to make it distinguishable from numbered 1 cards even though it could be 1. Figure out dual rank???)
	// then it is ace. Rank 10 could be 10 or any of the face cards. So, for ease of calculation from 10, make bool???
	bool _isRoyal;

private:


};
