#pragma once
#include "effect.h"
#include "player.h"
#include "game_system.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

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

	static sf::Texture spritesheet;
	static float tileWidth;
	static float tileHeight;
	static int windowWidth;
	static int windowHeight;

	static sf::Font font;
};