#include "suit.h"

Suit::Suit(Effect effect) : effects({ effect }) {};
Suit::Suit(std::vector<Effect> effects) : effects(effects) {};

std::vector<Effect> Suit::getSuitEffects() {
	return Suit::effects;
}