#include "effect.h"

Effect::Effect(bool isPositive, int damage, int healing, int damageIncrease, int healingIncrease, float damageDecresePercentage, int damageResist) :
	positiveEffect(isPositive), damage(damage), healing(healing), damageIncrease(damageIncrease), 
	healingIncrease(healingIncrease), damageDecreasePercent(damageDecresePercentage), damageResist(damageResist) { }


bool Effect::getIsPositiveEffect() {
	return Effect::positiveEffect;
}

int Effect::getDamage() {
	return Effect::damage;
}

int Effect::getHealing() {
	return Effect::healing;
}

int Effect::getDamageIncrease() {
	return Effect::damageIncrease;
}

int Effect::getHealingIncrease() {
	return Effect::healingIncrease;
}

float Effect::getDamageDecreasePercent() {
	return Effect::damageDecreasePercent;
}

int Effect::getDamageResist() {
	return Effect::damageResist;
}