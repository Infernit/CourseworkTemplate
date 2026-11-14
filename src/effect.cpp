#include "effect.h"

Effect::Effect() : isPositive(false), effectType(none), value(0) {};
Effect::Effect(bool isPositive, EffectType type, float value) : isPositive(isPositive), effectType(type), value(value) {};

bool Effect::getIsPositiveEffect() {
	return Effect::isPositive;
}

EffectType Effect::getEffectType() {
	return Effect::effectType;
}

float Effect::getValue() {
	return Effect::value;
}

// To string for the class for test printing
std::string Effect::toString() {
	std::string effectTypeString;

	switch (Effect::effectType) {
		case none:
			effectTypeString = "none";
			break;
		case damage:
			effectTypeString = "damage";
			break;
		case healing:
			effectTypeString = "heal";
			break;
		case damageIncrease:
			effectTypeString = "damage increase";
			break;
		case healingIncrease:
			effectTypeString = "healing increase";
			break;
		case damageDecreasePercent:
			effectTypeString = "damage decrease percent";
			break;
		case damageResist:
			effectTypeString = "damage resist";
			break;
		default:
			effectTypeString = "unknown";
			break;
	}

	return "Effect Type: " + effectTypeString + ", Is Positive: " + (isPositive ? "true" : "false") + ", Value: " + std::to_string(value);
}