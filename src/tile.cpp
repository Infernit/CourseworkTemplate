#include "tile.h"

Tile::Tile() {

}

Tile::Tile(int x, int y, bool occupied, int tileWidth, int tileHeight, sf::Color colour) {
	_x = x;
	_y = y;
	_occupied = occupied;

	_beingDragged = false;

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

sf::Sprite Tile::getCardSpriteVal() {
	return _cardSprite;
}

sf::Sprite* Tile::getCardSpriteRef()
{
	return &_cardSprite;
}

bool Tile::getBeingDragged()
{
	return _beingDragged;
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

void Tile::addCardDescBarSprite(sf::Sprite cardDescBarSprite)
{
	_cardDescBarSprite.push_back(cardDescBarSprite);
}

void Tile::addCardDescBarSprite(sf::Text cardDescBarSprite) {
	_cardDescBarText.push_back(cardDescBarSprite);
}

void Tile::resetCardDescBarSprites()
{
	_cardDescBarSprite = {};
	_cardDescBarText = {};
}

void Tile::setBeingDragged(bool value)
{
	_beingDragged = value;
}

void Tile::drawCardDescBarSprite(sf::RenderWindow& window)
{
	for (int i = 0; i < _cardDescBarSprite.size(); i++) {
		window.draw(_cardDescBarSprite[i]);
	}
	for (int i = 0; i < _cardDescBarText.size(); i++) {
		window.draw(_cardDescBarText[i]);
	}
}

void Tile::removeCardSprite() {
	// cannot reset so just set to nothing
	sf::Texture tempSprite;
	_cardSprite.setTexture(tempSprite);
}