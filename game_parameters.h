#pragma once
#include "effect.h"
#include <string>
#include <vector>

struct GameParameters {
	static Effect getHeartEffect();
	static Effect getDiamondEffect1();
	static Effect getDiamondEffect2();
	static Effect getDiamondEffect3();
	static Effect getClubEffect();
	static Effect getSpadeEffect();

	static int handSize;
	static int startingEnergy;
	static std::vector<std::string> suitNames;
};