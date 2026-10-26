#include "card.h"

Card::Card() {};

Card::Card(Suit suit, int rank)
	: cardSuit(suit), cardRank(rank), cardEffects({})
{
	int size = suit.getSuitEffects().size();
	std::vector<Effect> array(size);

	for (int i = 0; i < size; i++) {
		array[i] = Effect(suit.getSuitEffects()[i].getIsPositiveEffect(),
			suit.getSuitEffects()[i].getEffectType(),
			suit.getSuitEffects()[i].getValue() * rank);
	}

	cardEffects = array;
};

std::vector<Effect> Card::getCardEffects() {
	return cardEffects;
}