#pragma once
#include "card.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Board {

public:
	Board();
	void init();
	static const int tileWidth;
	static const int tileHeight;
	static unsigned int windowWidth;
	static unsigned int windowHeight;
	static std::vector<sf::Sprite> cards;
	sf::Vector2f gridToPixels(int gridX, int gridY);
	// in cpp: std::vector<sf::Sprite> cards;

private:
	std::vector<Card> side1Cards;
	std::vector<Card> side2Cards;
};