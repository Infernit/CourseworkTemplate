#include "testing.h"
#include <vector>
#include <iostream>

using params = GameParameters;
using namespace std;

void Testing::kill_player() {
	GameSystem system;
	system.createPlayers(false);
	system.getPlayer1()->reduceHealth(1);
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

void Testing::fill_player_hand() {
	GameSystem system;
	system.createPlayers(false);
	// Loops 100 times to check if the hand size validation works
	for (int i = 0; i < 100; i++) {
		system.getPlayer1()->drawCard();
	}
	
	std::cout << std::endl;
	std::cout << "Hand contents" << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < params::handSize; i++) {
		std::cout << params::cardNames[system.getPlayer1()->getHand()[i].getCardRank()] << " of " << params::suitNames[system.getPlayer1()->getHand()[i].getCardSuit().getSuitName()] << std::endl;
	}
}

void Testing::testing_effects_stuff() {
	GameSystem system;
	system.setMaxEnergy(10);
	Deck deck;

	std::vector<Card> cards = deck.getCards();
	Card card;
	Card card2;

	for (int i = 0; i < cards.size(); i++) {
		if (cards[i].getCardSuit().getSuitName() == hearts && cards[i].getCardRank() == 8) {
			card = cards[i];
		}
		else if (cards[i].getCardSuit().getSuitName() == clubs && cards[i].getCardRank() == 10) {
			card2 = cards[i];
		}
	}

	Player player(false, system);

	std::cout << "player health pre attack: " << player.getHealth() << std::endl;

	card2.applyCardEffect(&player);

	std::cout << "player health post attack: " << player.getHealth() << std::endl;
	

	card2.reduceHealth(5);

	std::cout << "card health pre heal" << card2.getCardHealth() << std::endl;

	card.applyCardEffect(&card2);

	std::cout << "card health post heal" << card2.getCardHealth() << std::endl;
}