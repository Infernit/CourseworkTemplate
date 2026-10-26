#pragma once
#include "effect.h"
#include <vector>

class Suit {

public:
	Suit();
	Suit(Effect effect);
	Suit(std::vector<Effect> effects);

	std::vector<Effect> getSuitEffects();

protected:
	std::vector<Effect> effects;


private:
	

};