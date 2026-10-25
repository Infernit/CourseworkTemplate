#pragma once

class Effect {

public:
	Effect(bool isPositive, int damage, int healing, int damageIncrease, int healthIncrease, float damageDecresePercentage, int damageResist);
	bool getIsPositiveEffect();
	int getDamage();
	int getHealing();
	int getDamageIncrease();
	int getHealingIncrease();
	float getDamageDecreasePercent();
	int getDamageResist();

protected:
	

private:
	bool positiveEffect; //H: True, D: True, C: False, S: False
	int damage; //H: 0, D: 0, C: 1-10, S: 0
	int healing; //H: 1-10, D: 0, C: 0, S: 0
	int damageIncrease; //H: 0, D: 1-10, C: 0, S: 0
	int healingIncrease; //H: 0, D: 1-10, C: 0, S: 0
	float damageDecreasePercent; //H: 0, D: 0, C: 0, S: 0.1-1.0
	int damageResist; //H: 0, D: 1-10, C: 0, S: 0

	// Diamonds will provide all buffs when applied, but be removed as soon as one is used.
	// For the effects in the suit classes, set all values to lowest, then when effect is added to the card times by rank.

};