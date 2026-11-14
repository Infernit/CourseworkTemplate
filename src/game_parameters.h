#pragma once
#include "effect.h"
#include "player.h"
#include "game_system.h"
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
	static std::vector<std::string> cardNames;
	static std::vector<std::string> suitNames;
};