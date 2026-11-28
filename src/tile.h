#pragma once
#include "game_parameters.h"
#include <SFML/Graphics.hpp>

class Tile {
// It will have an x and y, and a bool
public:
	// Constructor
	Tile();
	Tile(int x, int y, bool occupied, int tileWidth, int tileHeight, sf::Color colour);

	// Getters
	bool getOccupuied();
	int getX();
	int getY();	
	sf::RectangleShape getShape();
	sf::Sprite getCardSpriteVal();
	sf::Sprite* getCardSpriteRef();
	bool getBeingDragged();

	// Setters
	void setColour(sf::Color colour);
	void setSize(float size);
	void setOccupied(bool occupied);
	void setCardSprite(sf::Sprite cardSprite);
	void addCardDescBarSprite(sf::Sprite cardDescBarSprite);
	void addCardDescBarSprite(sf::Text cardDescBarSprite);
	void resetCardDescBarSprites();
	void setBeingDragged(bool value);

	void drawCardDescBarSprite(sf::RenderWindow& window);

	// Helpers
	void removeCardSprite();

private:
	// Attributes
	int _x;
	int _y;
	bool _occupied;
	sf::RectangleShape _shape;
	sf::Sprite _cardSprite;
	std::vector<sf::Sprite> _cardDescBarSprite;
	std::vector<sf::Text> _cardDescBarText;

	bool _beingDragged;
};
