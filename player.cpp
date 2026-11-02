#include "player.h"

Player::Player() {
	populateDeck();
}

void Player::populateDeck() {
	Deck deck;
	Player::_deck = deck;
}

Deck Player::getDeck() {
	return _deck;
}

void Player::reduceHealth(int value) {
	_health -= value;

	if (_health <= 0) {
		__raise Player::PlayerKilled();
	}
}