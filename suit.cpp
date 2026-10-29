#include "suit.h"

Suit::Suit() {};
Suit::Suit(SuitName suitName, Effect effect) : _effects({ effect }), _suitName(suitName) {};
Suit::Suit(SuitName suitName, std::vector<Effect> effects) : _effects(effects), _suitName(suitName) {};

std::vector<Effect> Suit::getSuitEffects() {
	return Suit::_effects;
}

SuitName Suit::getSuitName() {
	return Suit::_suitName;
}