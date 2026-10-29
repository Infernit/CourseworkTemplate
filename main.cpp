#include "card.h"
#include "deck.h"
#include <iostream>
#include <string>
#include <vector>
#include "game_parameters.h"
#include "suit.h"

using params = GameParameters;

int main()
{
	Deck testDeck;
	int deckSize = testDeck.getCards().size();
	testDeck.shuffleDeck();

	for (int i = 0; i < deckSize + 1; i++) {
		Card card = testDeck.drawNextCard();
		int rank = card.getCardRank();
		int suitEnumResult = card.getCardSuit().getSuitName();

		std::cout << params::cardNames[rank] << " of " << params::suitNames[suitEnumResult] << std::endl;
	}
}