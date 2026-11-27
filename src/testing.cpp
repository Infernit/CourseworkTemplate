#include "testing.h"
#include <vector>
#include <iostream>
#include "board.h"

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
	system.init();
	GameSystem::setMaxEnergy(GameParameters::startingEnergy);

	Player* player1 = system.getPlayer1();
	Player* player2 = system.getPlayer2();

	player1->fillHand();
	player2->fillHand();

	//Create board
	Board board(&system);
	//Havent bothered validating this as it wont be the final version

	Player* player = player1;
	Player* opponent = player2;

	sf::RenderWindow window(sf::VideoMode({ (unsigned)GameParameters::windowWidth, (unsigned)GameParameters::windowHeight }), "SFML works!");
	
	//Outmost loop, loops until a player dies.
	while (player1->getHealth() > 0 && player2->getHealth() > 0) {

		std::cout 
			<< std::endl 
			<< "ROUND " 
			<< GameParameters::turnNumber
			<< ": Player 1 HP = " 
			<< player1->getHealth() 
			<< ", Player 2 HP = " 
			<< player2->getHealth() 
			<< std::endl 
			<< std::endl;

		//Player 1 turn stuff
		if (system.getTurn() == 1) {
			player = player1;
			opponent = player2;
		}
		//Player 2 turn stuff
		else {
			player = player2;
			opponent = player1;
		}

		//Changing turn
		std::cout << "\x1b[2J";

		int temp = 0;
		std::cout << "TYPE A NUMBER AND PRESS ENTER TO START NEXT TURN";
		std::cin >> temp;

		std::cout
			<< std::endl
			<< "PLAYER "
			<< system.getTurn()
			<< "'S TURN"
			<< std::endl
			<< std::endl;

		//Set player energy to current max energy
		player->setCurrentEnergy(GameSystem::getMaxEnergy());

		//Fill players hand from deck
		player->fillHand();
		board.aceDamageCard(player);

		board.setPlayerCardsUsable(player);

		//==============TESTING=============//
		//COMMENT THIS OUT FOR A STANDARD GAME
		//Replace below card with card that needs testing
		/*
		Suit spadesSuit(clubs, GameParameters::getClubEffect());
		Card jackOfSpades(spadesSuit, 13);
		//player->setCurrentEnergy(12);
		player->forceCardIntoHand(jackOfSpades);
		*/

		board.placeCardsOnBoard(player1, player2, window);
		window.display();

		//Play cards from hand
		while (player->getCurrentEnergy() > 0) {
			// Turn number
			std::cout
				<< "Turn Number: "
				<< GameParameters::turnNumber
				<< std::endl
				<< "-----------------"
				<< std::endl;

			std::cout
				<< "Current Energy: "
				<< player->getCurrentEnergy()
				<< std::endl
				<< "-----------------"
				<< std::endl;

			//List player cards
			for (int i = 0; i < player->getHand().size(); i++) {
				std::cout
					<< i + 1
					<< ": "
					<< params::cardNames[player->getHand()[i].getCardRank()]
					<< " of "
					<< params::suitNames[player->getHand()[i].getCardSuit().getSuitName()]
					<< std::endl;
			}

			std::cout << "0: Manually End Turn" << std::endl;

			//Get user input
			std::cout 
				<< std::endl 
				<< "Pick card to play: ";
			int num;
			std::cin >> num;

			//Try play card based on user input
			if (num == 0) {
				break;
			}
			else if (!board.playCard(player, opponent, player->getHand()[num - 1])) {
				std::cout
					<< std::endl
					<< "Invalid Option"
					<< std::endl
					<< std::endl;
			}
		}

		//Play cards on board
		bool keepLooping = true;

		while (keepLooping) {
			//Lower flag by default
			keepLooping = false;

			std::cout
				<< std::endl
				<< "Playable Cards:"
				<< std::endl
				<< "---------------"
				<< std::endl;

			int index = 1;

			//List usable player cards
			for (Card card : board.getFriendlyCards(player)) {
				std::cout
					<< index
					<< ": "
					<< params::cardNames[card.getCardRank()]
					<< " of "
					<< params::suitNames[card.getCardSuit().getSuitName()]
					<< " - HP: "
					<< card.getCardHealth()
					<< " - OH: "
					<< card.getOverhealth()
					<< ", DB: "
					<< card.getEffectIncreases()
					<< ", DD: "
					<< card.getDamageDecrease()
					<< ", Usable? "
					<< (card.getIsUsable() ? "True" : "False")
					<< std::endl;

				index++;

				//Raise flag if player has usable card on board
				if (card.getIsUsable()) {
					keepLooping = true;
				}
			}

			if (!keepLooping) {
				break;
			}

			std::cout << std::endl;

			//Get user input
			std::cout << "Pick card to use: ";
			int num1;
			std::cin >> num1;

			std::cout << std::endl;

			//SWITCH CASE
				
			Card* cardToUse = &board.getFriendlyCards(player)[num1 - 1];

			if (cardToUse->getIsUsable()) {
				board.playCardRankAndSuit(player, opponent, *cardToUse);
			}
			else {
				std::cout << "Card cannot be used" << std::endl;
			}
				
			//... SPECIAL CARD
			//LOOP THROUGH ALL CARDS AND EFFECT THEM
			//modified version of tryPlayCardToEffectable that just effects all of them instead of targeting.
		}

		board.resetDamageDebuffs(player);
		
		/*
		if (params::startingEnergy < 10) {
			params::startingEnergy++;
		}
		*/
		if (system.getTurn() == 2 && !system.getSkipTurn()) {

			// Turn number and energy increase together
			GameSystem::setMaxEnergy(GameSystem::getMaxEnergy() + 1);
			params::turnNumber++;

			// Loop through each players hand and deck if turn  number 11 is reached

			if (GameSystem::getMaxEnergy() == 11) {
				// PLAYER 1
				// Loop deck
				player1->turnHandAcesInto11Aces();

				player1->turnDeckAcesInto11Aces();

				
				player2->turnHandAcesInto11Aces();

				player2->turnDeckAcesInto11Aces();
			}

			//round++;
		}

		system.nextTurn();
	}
}