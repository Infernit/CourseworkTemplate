#include "testing.h"
#include <vector>
#include <iostream>
#include "board_functionality.h"

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
	Card eightHearts;
	Card tenClubs;
	Card sixSpades;
	Card twoSpades;
	Card sevenDiamonds;
	Card nineClubs;

	for (int i = 0; i < cards.size(); i++) {
		if (cards[i].getCardSuit().getSuitName() == hearts && cards[i].getCardRank() == 8) {
			eightHearts = cards[i];
		}
		else if (cards[i].getCardSuit().getSuitName() == clubs && cards[i].getCardRank() == 10) {
			tenClubs = cards[i];
		}
		else if (cards[i].getCardSuit().getSuitName() == spades && cards[i].getCardRank() == 6) {
			sixSpades = cards[i];
		}
		else if (cards[i].getCardSuit().getSuitName() == spades && cards[i].getCardRank() == 2) {
			twoSpades = cards[i];
		}
		else if (cards[i].getCardSuit().getSuitName() == clubs && cards[i].getCardRank() == 9) {
			nineClubs = cards[i];
		}
		else if (cards[i].getCardSuit().getSuitName() == diamonds && cards[i].getCardRank() == 7) {
			sevenDiamonds = cards[i];
		}

	}

	//10 of clubs attacking player on 100 health
	//should reduce health by 10 (resulting in 90)
	Player player(false, system);

	std::cout << "player health pre attack: " << player.getHealth() << std::endl;

	tenClubs.applyCardEffect(&player);

	std::cout << "player health post attack: " << player.getHealth() << std::endl;
	
	//8 of hearts healing 10 of clubs on 15 health
	//Should only heal 5, even though the card can heal 8 due to max health restrictions
	tenClubs.reduceHealth(5);

	std::cout << "card health pre heal: " << tenClubs.getCardHealth() << std::endl;

	eightHearts.applyCardEffect(&tenClubs);

	std::cout << "card health post heal: " << tenClubs.getCardHealth() << std::endl;

	//Applying the 7 of diamonds to the 10 of clubs should give it 7 damage resist
	sevenDiamonds.applyCardEffect(&tenClubs);
	 
	//Hitting the 10 of clubs with the 9 of clubs will do 7 damage to resist and 2 to the card
	std::cout << "card health pre attack: " << tenClubs.getCardHealth() << " plus resist: " << to_string(tenClubs.getEffectIncreases()) << std::endl;

	nineClubs.applyCardEffect(&tenClubs);

	std::cout << "card health post attack: " << tenClubs.getCardHealth() << " plus resist: " << to_string(tenClubs.getEffectIncreases()) << std::endl;

	//Applying the 6 of spades and the 2 of spades to the 10 of clubs should reduce it's damage by 68% to 32% of 10 (with int rounding that comes out to 3)
	sixSpades.applyCardEffect(&tenClubs);
	twoSpades.applyCardEffect(&tenClubs);

	std::cout << "player health pre attack: " << player.getHealth() << std::endl;

	tenClubs.applyCardEffect(&player);

	std::cout << "player health post attack: " << player.getHealth() << std::endl;



}

void Testing::mockup_round() {
	//Initialise Game System
	GameSystem system;
	system.setMaxEnergy(2);

	//Create players, with both being human
	system.createPlayers(false);

	Player* player1 = system.getPlayer1();
	player1->fillHand();

	for (int i = 0; i < player1->getHand().size(); i++) {
		std::cout << i+1 << ": " << params::cardNames[player1->getHand()[i].getCardRank()] << " of " << params::suitNames[player1->getHand()[i].getCardSuit().getSuitName()] << std::endl;
	}

	//Havent bothered validating this as it wont be the final version
	std::cout << "Pick card to play: ";
	int num;
	cin >> num;

	BoardFunctionality board;

	board.playCard(1, &player1->getHand()[num - 1]);
	
}