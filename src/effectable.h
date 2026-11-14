#pragma once
#include <vector>
#include "effect.h"

class Effectable {
public:
	virtual bool reduceHealth(int value) = 0;
	virtual void increaseHealth(int value) = 0;
	virtual bool applyEffect(Effect effect) = 0;
protected:
	int _health = 0;
	int _maxHealth = 0;
	std::vector<Effect> _appliedEffects;
};