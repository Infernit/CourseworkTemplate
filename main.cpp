#include "card.h"
#include <iostream>

int main()
{
	// Heart Cards Heal
	Effect heartEffect(true, healing, 1.0f);

	// Diamond Cards Will Have One Of The Following Effects
	Effect diamondEffect1(true, damageIncrease, 1.0f);
	Effect diamondEffect2(true, healingIncrease, 1.0f);
	Effect diamondEffect3(true, damageResist, 1.0f);

	// Club Cards Deal Damage
	Effect clubEffect(false, damage, 1.0f);

	// Spade Cards Reduce Outgoing Damage
	Effect spadeEffect(false, damageDecreasePercent, 0.1f);

	Suit hearts(heartEffect);
	Suit diamonds({ diamondEffect1, diamondEffect2, diamondEffect3 });
	Suit clubs(clubEffect);
	Suit spades(spadeEffect);
	
	Card eightofSpades(spades, 8);

	std::cout << eightofSpades.getCardEffects()[0].getValue() << std::endl;

}