#pragma once
#include "effect.h"
#include "player.h"
#include "game_system.h"
#include <vector>
#include <string>

struct GameParameters {
	static Effect getHeartEffect();
	static Effect getDiamondEffect();
	static Effect getClubEffect();
	static Effect getSpadeEffect();

	static int handSize;
	static int startingEnergy;
	static int maxPlayerHealth;
	static int boardSize;
	static std::vector<std::string> cardNames;
	static std::vector<std::string> suitNames;
};