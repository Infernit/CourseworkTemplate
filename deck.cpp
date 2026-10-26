#include "deck.h"
#include "game_parameters.h"

Deck::Deck(int value) {
	populateSuits();
	populateDeck();
};

int Deck::getCardCount() {
	return _cards.size();
}

std::vector<Card> Deck::getCards() {
	return _cards;
}

/*
Card Deck::drawNextCard() {
	//Leaving this for now
	
}

void Deck::shuffleDeck() {
	//Might be complicated
}
*/

void Deck::populateDeck() {
	std::vector<Card> cards(0);

	GameParameters params = GameParameters::getInstance();

	for (int i = 0; i < _suits.size(); i++) {
		for (int j = 0; j < 10; j++) {
			Card card(_suits[i], j);
			cards.push_back(card);
		}
	}

	_cards = cards;
}

void Deck::populateSuits() {
	std::vector<Suit> suits(4);

	GameParameters params = GameParameters::getInstance();

	Suit hearts(params.getHeartEffect());
	suits[0] = hearts;
	Suit diamonds({ params.getDiamondEffect1(), params.getDiamondEffect2(), params.getDiamondEffect3() });
	suits[1] = diamonds;
	Suit clubs(params.getClubEffect());
	suits[2] = clubs;
	Suit spades(params.getSpadeEffect());
	suits[3] = spades;

	_suits = suits;
}