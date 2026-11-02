#pragma once
#include "effect.h"
#include <vector>
#include <string>

struct GameParameters {
	static Effect getHeartEffect();
	static Effect getDiamondEffect1();
	static Effect getDiamondEffect2();
	static Effect getDiamondEffect3();
	static Effect getClubEffect();
	static Effect getSpadeEffect();

	static int handSize;
	static int startingEnergy;
	static int startingHealth;
	static std::vector<std::string> cardNames;
	static std::vector<std::string> suitNames;
};