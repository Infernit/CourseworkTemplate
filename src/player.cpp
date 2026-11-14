#include "game_parameters.h"
#include "player.h"
#include "deck.h"
#include "game_system.h"

Player::Player(bool isAI, GameSystem& system) : _isAI(isAI), _system(system) {
	std::vector<Card> hand(0);
	Player::_hand = hand;
	Player::populateDeck();
	Player::_playerNumber = system.getNextPlayerNumber();
	_system.hookPlayerKilled(this);
}

Player::~Player() {
	_system.unhookPlayerKilled(this);
}

void Player::drawCard() {
	if (_hand.size() == GameParameters::handSize) {
		return;
	}

	_hand.push_back(Player::_deck.drawNextCard());
}

void Player::populateDeck() {
	Deck deck;
	deck.shuffleDeck();
	Player::_deck = deck;
}

Deck Player::getDeck() {
	return Player::_deck;
}

//Returns true if player died, false if lived
bool Player::reduceHealth(int value) {
	Player::_health -= value;

	if (Player::_health <= 0) {
		__raise Player::PlayerKilled(Player::_playerNumber);
		return true;
	}

	return false;
}

std::vector<Card> Player::getHand() {
	return _hand;
}