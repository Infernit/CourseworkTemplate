#include "suit.h"

Suit::Suit() : _suitName(noSuit) {}
Suit::Suit(SuitName suitName, Effect effect) : _effects({ effect }), _suitName(suitName) {};
Suit::Suit(SuitName suitName, std::vector<Effect> effects) : _effects(effects), _suitName(suitName) {};

std::vector<Effect> Suit::getSuitEffects() {
	return Suit::_effects;
}

SuitName Suit::getSuitName() {
	return Suit::_suitName;
}

// To string for the class for test printing
std::string Suit::toString() {
	std::string effectsString = "";
	for (Effect effect : _effects) {
		effectsString += effect.toString() + ", ";
	}
	return "Suit Name: " + GameParameters::suitNames[_suitName] + ", Effects: [" + effectsString + "]";
}