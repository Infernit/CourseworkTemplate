#pragma once
#include "suit.h"

class Card {

public:
	Card(Suit& suit, int rank);
	Effect getCardEffect();

protected:
	Suit& cardSuit;
	int cardRank;
	Effect cardEffect;


private:


};
