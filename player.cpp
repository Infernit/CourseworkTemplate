#include "player.h"
#include "game_system.h"
#include "deck.h"

Player::Player() {
	Player::populateDeck();
	Player::_playerNumber = GameSystem::getNextPlayerNumber();
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