#include "game_parameters.h"
#include "player.h"
#include "game_system.h"
#include "deck.h"
#include "card.h"
#include <iostream>

using params = GameParameters;

int main()
{
	Player player;

	GameSystem system;

	system.hookPlayerKilled(&player);

	player.reduceHealth(1);


	Deck testDeck;
	int deckSize = testDeck.getCards().size();
	testDeck.shuffleDeck();

	for (int i = 0; i < deckSize + 1; i++) {
		Card card = testDeck.drawNextCard();
		int rank = card.getCardRank();
		int suitEnumResult = card.getCardSuit().getSuitName();

		std::cout << params::cardNames[rank] << " of " << params::suitNames[suitEnumResult] << std::endl;
		// Test new to string methods for classes
		std::cout << card.toString() << std::endl;
		//std::cout << card.getCardRank() << " of " << params::suitNames[enumResult] << std::endl;
	}
}