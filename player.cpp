#include "player.h"
#include "game_system.h"
#include "deck.h"

Player::Player(bool isAI, GameSystem system) : _isAI(isAI), _system(system) {
	Player::populateDeck();
	Player::_playerNumber = GameSystem::getNextPlayerNumber();
	_system.hookPlayerKilled(this);
}

Player::~Player() {
	_system.unhookPlayerKilled(this);
}

void Player::populateDeck() {
	Deck deck;
	Player::_deck = deck;
}

Deck Player::getDeck() {
	return Player::_deck;
}

void Player::reduceHealth(int value) {
	Player::_health -= value;

	if (Player::_health <= 0) {
		__raise Player::PlayerKilled(Player::_playerNumber);
	}
}