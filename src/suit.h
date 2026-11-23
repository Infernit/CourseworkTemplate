#pragma once
#include "effect.h"
#include <vector>
#include <string>

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

	Effect getSuitEffect();
	SuitName getSuitName();
	std::string toString();

private:
	Effect _effect;
	SuitName _suitName;
};