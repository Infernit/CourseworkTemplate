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
	_maxHealth = GameParameters::maxPlayerHealth;
	_health = _maxHealth;
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

int Player::getHealth()
{
	return _health;
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

void Player::increaseHealth(int value) {
	_health += value;

	if (_health > _maxHealth) {
		_health = _maxHealth;
	}
}

bool Player::applyEffect(Effect effect) {
	switch (effect.getEffectType()) {
	case damage:
		reduceHealth(effect.getValue());
		break;

	case healing:
		increaseHealth(effect.getValue());
		break;

	case damageIncrease:
		//increaseEffect(effect.getValue(), damage);
		break;

	case healingIncrease:
		//increaseEffect(effect.getValue(), healing);
		break;

	case damageDecreasePercent:
		//damage decrease percent method
		break;

	case damageResist:
		//damage resist method
		break;

	default:
		std::cout << "No effect applied" << std::endl;
		break;
	}

	return true;
}

std::vector<Card> Player::getHand() {
	return _hand;
}