#include "tile.h"

Tile::Tile() {

}

Tile::Tile(int x, int y, bool occupied, int tileWidth, int tileHeight, sf::Color colour) {
	_x = x;
	_y = y;
	_occupied = occupied;

	// sfml properties
	_shape = sf::RectangleShape();
	_shape.setSize(sf::Vector2f((GameParameters::tileWidth + GameParameters::cardDescBarWidth), GameParameters::tileHeight));
	_shape.setFillColor(colour);
	_shape.setPosition(x * (GameParameters::tileWidth + GameParameters::cardDescBarWidth), y * GameParameters::tileHeight + GameParameters::healthBarHeight);
	_shape.setOutlineThickness(1.f);
	_shape.setOutlineColor(sf::Color::Black);
}

bool Tile::getOccupuied() {
	return _occupied;
}

int Tile::getX() {
	return _x;
}

int Tile::getY() {
	return _y;
}

sf::RectangleShape Tile::getShape() {
	return _shape;
}

sf::Sprite Tile::getCardSprite() {
	return _cardSprite;
}

void Tile::setColour(sf::Color colour)
{
}

void Tile::setSize(float size)
{
}

void Tile::setOccupied(bool occupied) {
	_occupied = occupied;
}

void Tile::setCardSprite(sf::Sprite cardSprite) {
	_cardSprite = cardSprite;
}

void Tile::removeCardSprite() {
	// cannot reset so just set to nothing
	sf::Texture tempSprite;
	_cardSprite.setTexture(tempSprite);
}