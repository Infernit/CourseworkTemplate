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