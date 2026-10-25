#pragma once
#include "effect.h"

class Suit {

public:
	Suit(Effect effect);

	virtual ~Suit() = default;

	virtual Effect getSuitEffect() const = 0;

protected:
	Effect effect;


private:
	

};