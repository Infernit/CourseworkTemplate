#pragma once
#include "effect.h"
#include <vector>

enum SuitName {
	noSuit,
	hearts,
	diamonds,
	clubs,
	spades,
};

class Suit {

public:
	Suit();
	Suit(SuitName suitName, Effect effect);
	Suit(SuitName suitName, std::vector<Effect> effects);

	std::vector<Effect> getSuitEffects();
	SuitName getSuitName();

private:
	std::vector<Effect> _effects;
	SuitName _suitName;

};