#pragma once
#include <string>

class Effectable;

enum EffectType {
	none,
	damage,
	healing,
	diamondEffect,
	damageDecreasePercent,
};

class Effect {

public:
	Effect();
	Effect(bool isPositive, EffectType type, float value);
	bool applyEffect(Effectable* damagable);
	bool getIsPositiveEffect();
	bool getIsSpreadableEffect();
	EffectType getEffectType();
	float getValue();
	std::string toString();
	// Property of effect: Spread

	// Queen clubs damages all played cards, 
	// Jack spades doubles all energy cost of hand cards,
	// Queen spades halves all enemy damage of played cards,
	// Jack diamonds halves energy cost of player hand cards,
	// King diamonds grants all played cards 10 extra health,
	// Jack hearts removes all debuffs from played cards

	//* Heart Ace heals all played cards by 5 every turn present
	bool spreadable;
	bool gravyardInteractable;

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