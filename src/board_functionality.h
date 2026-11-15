#pragma once
#include <vector>
#include "card.h"

class BoardFunctionality {
public:
	BoardFunctionality();

	bool playCard(int playerNumber, Card* card);


private:
	std::vector<Card*> player1BoardCards;
	std::vector<Card*> player2BoardCards;
};