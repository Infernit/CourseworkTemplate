#pragma once
#include "card.h"
#include "deck.h"
#include "effect.h"
#include "game_system.h"
#include "player.h"
#include "suit.h"
#include <string>
#include <vector>
#include <ctime>
#include <iostream>

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