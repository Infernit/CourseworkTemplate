#pragma once
#include <vector>
#include "effect.h"

class Effectable {
public:
	virtual bool reduceHealth(int value) = 0;
protected:
	int _health;
	std::vector<Effect> _appliedEffects;
};