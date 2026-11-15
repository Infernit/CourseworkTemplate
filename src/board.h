#pragma once
#include "card.h"
#include <vector>

class Board {

public:
	Board();
	void init();
	static const int tileWidth;
	static const int tileHeight;

private:
	std::vector<Card> side1Cards;
	std::vector<Card> side2Cards;
};