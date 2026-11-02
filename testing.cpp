#include "testing.h"
#include <vector>
#include <iostream>

using params = GameParameters;
using namespace std;

void Testing::kill_player() {

	Player player;
	GameSystem system;

	system.hookPlayerKilled(&player);
	player.reduceHealth(1);

}

void Testing::test_deck_attributes() {

	Deck testDeck;
	int deckSize = testDeck.getCards().size();
	testDeck.shuffleDeck();

	for (int i = 0; i < deckSize + 1; i++) {
		Card card = testDeck.drawNextCard();
		int rank = card.getCardRank();
		int suitEnumResult = card.getCardSuit().getSuitName();

		std::cout << params::cardNames[rank] << " of " << params::suitNames[suitEnumResult] << std::endl;
		// Test new to string methods for classes
		std::cout << card.toString() << std::endl << std::endl << std::endl;
		//std::cout << card.getCardRank() << " of " << params::suitNames[enumResult] << std::endl;
	}

}

// Test that royals and other cards (excluding graveyard ace) and their rules can be created using current params via effects and card class
void Testing::develop_effect_testing() {
	std::cout << "Developing effect testing test statement" << std::endl;

	// Queen of spades
	//Card card
}