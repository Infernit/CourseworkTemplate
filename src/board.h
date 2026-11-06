#pragma once
#include "card.h"
#include <vector>

class Board {

public:
	Board();
	void init();

private:
	std::vector<Card> side1Cards;
	std::vector<Card> side2Cards;
};