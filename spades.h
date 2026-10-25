#pragma once
#include "suit.h"

class Spades : public Suit {

public:
	Spades(Effect effect) : Suit(effect) {}; // Call base constructor

	Effect getSuitEffect() const override;


protected:
	

private:


};