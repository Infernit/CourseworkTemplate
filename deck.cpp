#include "deck.h"

using params = GameParameters;

Deck::Deck() {
	populateSuits();
	populateDeck();
};

int Deck::getCardCount() {
	return _cards.size();
}

std::vector<Card> Deck::getCards() {
	return _cards;
}


Card Deck::drawNextCard() {
	//Best i can do for now
	if (_cards.size() == 0) {
		Card card;
		return card;
	}

	Card card = _cards[0];
	// Reduce the size of the deck
	std::vector<Card> cards(_cards.size() - 1);

	// Move all cards towards the front of the deck
	for (int i = 0; i < _cards.size() - 1; i++) {
		_cards[i] = _cards[i + 1];
		cards[i] = _cards[i];
	}

	_cards = cards;

	return card;
}

void Deck::shuffleDeck() {
	//Might be complicated
	
	std::vector<int> possibleIndexes(_cards.size());

	for (int i = 0; i < _cards.size(); i++) {
		possibleIndexes[i] = i;
	}

	// Get a different random number each time the program runs
	srand(time(0));
	// Generate a random number between 0 and 100
	

	std::vector<Card> cards(_cards.size());

	for (int i = 0; i < _cards.size(); i++) {
		int randomNum = possibleIndexes[rand() % possibleIndexes.size()];

		// Remove index from possible indexes as it has been assigned
		possibleIndexes.erase(std::remove(possibleIndexes.begin(), possibleIndexes.end(), randomNum), possibleIndexes.end());
		cards[randomNum] = _cards[i];
	}

	_cards = cards;
}


void Deck::populateDeck() {
	std::vector<Card> cards(0);

	for (int i = 0; i < _suits.size(); i++) {
		for (int j = 0; j < 13; j++) {
			Card card(_suits[i], j + 1);
			cards.push_back(card);
		}
	}

	_cards = cards;
}

void Deck::populateSuits() {
	std::vector<Suit> suits(4);

	Suit hearts(hearts, params::getHeartEffect());
	suits[0] = hearts;
	Suit diamonds(diamonds, { params::getDiamondEffect1(), params::getDiamondEffect2(), params::getDiamondEffect3() });
	suits[1] = diamonds;
	Suit clubs(clubs, params::getClubEffect());
	suits[2] = clubs;
	Suit spades(spades, params::getSpadeEffect());
	suits[3] = spades;

	_suits = suits;
}

// To string for the class for test printing
std::string Deck::toString() {
	std::string cardsString = "";
	for (Card card : _cards) {
		cardsString += card.toString() + ", ";
	}

	return "Deck Size: " + std::to_string(_cards.size()) + ", Cards: [" + cardsString + "]";
}