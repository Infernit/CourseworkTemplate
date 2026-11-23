#include "game_parameters.h"

Effect GameParameters::getHeartEffect() {
	Effect effect(true, healing, 1.0f);
	return effect;
}

Effect GameParameters::getDiamondEffect(){
	Effect effect(true, diamondEffect, 1.0f);
	return effect;
}

Effect GameParameters::getClubEffect() {
	Effect effect(false, damage, 1.0f);
	return effect;
}

Effect GameParameters::getSpadeEffect() {
	Effect effect(false, damageDecreasePercent, 0.1f);
	return effect;
}

int GameParameters::handSize = 7;
int GameParameters::startingEnergy = 2;
int GameParameters::maxPlayerHealth = 100;
int GameParameters::boardSize = 5;
std::vector<std::string> GameParameters::cardNames = {"noRank", "ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king"};
std::vector<std::string> GameParameters::suitNames = {"noSuit", "hearts", "diamonds", "clubs", "spades"};
// more useful here than in board (accessible from anywhere)
// Sprites
sf::Texture GameParameters::spritesheet;
float GameParameters::tileWidth = 33;
float GameParameters::tileHeight = 45;