#pragma once
#include "game_parameters.h"
#include <SFML/Graphics.hpp>

class Tile {
	// It will have an x and y, and a bool
	public:
		// Constructor
		Tile(int x, int y, bool occupied, int tileWidth, int tileHeight, sf::Color colour);

		// Getters
		bool getOccupuied();
		int getX();
		int getY();	
		sf::RectangleShape getShape();
		sf::Sprite getCardSprite();

		// Setters
		void setColour(sf::Color colour);
		void setSize(float size);
		void setOccupied(bool occupied);
		void setCardSprite(sf::Sprite cardSprite);

		// Helpers
		void removeCardSprite();

	private:
		// Attributes
		int _x;
		int _y;
		bool _occupied;
		sf::RectangleShape _shape;
		sf::Sprite _cardSprite;

};
