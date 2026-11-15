#include "suit.h"
#include "game_parameters.h"

Suit::Suit() : _suitName(noSuit) {}
Suit::Suit(SuitName suitName, Effect effect) : _effect(effect), _suitName(suitName) {};

Effect Suit::getSuitEffect() {
	return Suit::_effect;
}

SuitName Suit::getSuitName() {
	return Suit::_suitName;
}

// To string for the class for test printing
std::string Suit::toString() {
	return "Suit Name: " + GameParameters::suitNames[_suitName] + ", Effect: " + _effect.toString();
}