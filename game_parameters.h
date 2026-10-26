#pragma once
#include "effect.h"

class GameParameters {
public:
	static GameParameters& getInstance();

	int getHandSize();
	int getStartingEnergy();

	Effect getHeartEffect();
	Effect getDiamondEffect1();
	Effect getDiamondEffect2();
	Effect getDiamondEffect3();
	Effect getClubEffect();
	Effect getSpadeEffect();

private:
	int _handSize = 7;
	int _startingEnergy = 2;
};