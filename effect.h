#pragma once
#include <string>

enum EffectType {
	none,
	damage,
	healing,
	damageIncrease,
	healingIncrease,
	damageDecreasePercent,
	damageResist,
};

class Effect {

public:
	Effect();
	Effect(bool isPositive, EffectType type, float value);
	bool getIsPositiveEffect();
	EffectType getEffectType();
	float getValue();
	std::string toString();

protected:
	

private:
	bool isPositive; //H: True, D: True, C: False, S: False
	EffectType effectType;
	float value;

	// Maybe change this system to have an enum declaring the type and then a value, apply multiple effects rather than one for diamonds.
	// So just have positiveEffect, enum and value (which will be a float) 

	// Diamonds will provide all buffs when applied, but be removed as soon as one is used.
	// For the effects in the suit classes, set all values to lowest, then when effect is added to the card times by rank.

};