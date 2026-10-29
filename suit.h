#pragma once
#include "effect.h"
#include <vector>

enum SuitName {
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
	std::string toString();

private:
	std::vector<Effect> _effects;
	SuitName _suitName;
};