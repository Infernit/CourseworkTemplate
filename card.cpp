#include "card.h"

Card::Card(Suit& suit, int rank)
	: cardSuit(suit), cardRank(rank), cardEffect(Effect(
		suit.getSuitEffect().getIsPositiveEffect(),
		suit.getSuitEffect().getDamage()* rank,
		suit.getSuitEffect().getHealing()* rank,
		suit.getSuitEffect().getDamageIncrease()* rank,
		suit.getSuitEffect().getHealingIncrease()* rank,
		suit.getSuitEffect().getDamageDecreasePercent()* rank,
		suit.getSuitEffect().getDamageResist()* rank)) {
};

Effect Card::getCardEffect() {
	return cardEffect;
}