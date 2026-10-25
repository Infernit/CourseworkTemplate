#include "spades.h"
#include "card.h"
#include <iostream>

int main()
{
	Effect heartEffect(true, 0, 1, 0, 0, 0.0f, 0);
	Effect diamondEffect(true, 0, 0, 1, 1, 0.0f, 1);
	Effect clubEffect(false, 1, 0, 0, 0, 0.0f, 0);
	Effect spadeEffect(false, 0, 0, 0, 0, 0.1f, 0);

	Spades spade(spadeEffect);

	Card eightofSpades(spade, 8);

	std::cout << eightofSpades.getCardEffect().getDamageDecreasePercent() << std::endl;

}