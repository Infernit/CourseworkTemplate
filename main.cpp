#include "card.h"
#include "deck.h"
#include <iostream>

int main()
{
	Deck testDeck(0);
	std::vector<Card> cards = testDeck.getCards();
}