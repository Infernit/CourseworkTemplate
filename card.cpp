#include "card.h"
#include <string>

Card::Card() : _cardRank(0) {};

Card::Card(Suit suit, int rank)
	: _cardSuit(suit), _cardRank(rank), _cardEffects({})
{
	int size = suit.getSuitEffects().size();
	std::vector<Effect> array(size);

	for (int i = 0; i < size; i++) {
		array[i] = Effect(suit.getSuitEffects()[i].getIsPositiveEffect(),
			suit.getSuitEffects()[i].getEffectType(),
			suit.getSuitEffects()[i].getValue() * rank);
	}

	_cardEffects = array;
};

std::vector<Effect> Card::getCardEffects() {
	return _cardEffects;
}

Suit Card::getCardSuit() {
	return _cardSuit;
}

int Card::getCardRank() {
	return _cardRank;
}

// To string for the class for test printing
std::string Card::toString() {
	std::string effectsString = "";
	for (Effect effect : _cardEffects) {
		effectsString += effect.toString() + ", ";
	}
	return "Card Rank: " + std::to_string(_cardRank) + ", Card Suit: [" + _cardSuit.toString() + "], Card Effects: [" + effectsString + "]";
}