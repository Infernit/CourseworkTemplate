#include "game_parameters.h"
#include "player.h"
#include "deck.h"
#include "game_system.h"
#include <algorithm>
#include <cmath>

Player::Player(bool isAI, GameSystem& system) : _isAI(isAI), _system(system) {
	std::vector<Card> hand(0);
	Player::_hand = hand;
	// Graveyard
	std::vector<Card> graveyard(0);
	Player::_graveyard = graveyard;
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

void Player::addToGraveyard(Card card) {
	_graveyard.push_back(card);
}

void Player::removeHandCard(Card card) {
	std::vector<Card> tempHand;

	for (int i = 0; i < _hand.size(); i++) {
		if (!(_hand[i].getCardRank() == card.getCardRank() &&
			_hand[i].getCardSuit().getSuitName() == card.getCardSuit().getSuitName())) {
			tempHand.push_back(_hand[i]);
		}
	}

	_hand = tempHand;
}

// When/if revived(?)
void Player::removeGraveyardCard(Card card) {
	std::vector<Card> tempGraveyard;

	for (int i = 0; i < _graveyard.size(); i++) {
		if (!(_graveyard[i].getCardRank() == card.getCardRank() &&
			_graveyard[i].getCardSuit().getSuitName() == card.getCardSuit().getSuitName())) {
			tempGraveyard.push_back(_graveyard[i]);
		}
	}

	_graveyard = tempGraveyard;
}

void Player::turnHandAcesInto11Aces()
{
	for (int i = 0; i < _hand.size(); i++) {
		if (_hand[i].getCardRank() == 1) {
			_hand[i].setCardEnergyCost(11);
		}
	}
}

void Player::turnDeckAcesInto11Aces()
{
	_deck.turnAcesInto11Aces();
}

bool Player::halfHandEnergyCost()
{
	for (int i = 0; i < _hand.size(); i++) {
		_hand[i].setCardEnergyCost(ceil((float)_hand[i].getCardEnergyCost() / 2.f));
	}
	return true;
}

bool Player::doubleHandEnergyCost()
{
	for (int i = 0; i < _hand.size(); i++) {
		_hand[i].setCardEnergyCost((_hand[i].getCardEnergyCost() * 2 > GameSystem::getMaxEnergy() ? GameSystem::getMaxEnergy() : _hand[i].getCardEnergyCost() * 2));
	}
	return true;
}

void Player::fillHand() {
	while (_hand.size() != GameParameters::handSize) {
		drawCard();
	}
}

void Player::populateDeck() {
	Deck deck;
	deck.shuffleDeck();
	Player::_deck = deck;
}

int Player::getPlayerNumber() {
	return _playerNumber;
}

int Player::getHealth()
{
	return _health;
}

int Player::getCurrentEnergy() {
	return _currentEnergy;
}

void Player::setCurrentEnergy(int value) {
	_deck.setMaxEnergy(value);
	_deck.shuffleDeck();
	_currentEnergy = value;
}

Deck& Player::getDeck() {
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

// PINEAPPLE
bool Player::applyEffect(Effect effect) {
	switch (effect.getEffectType()) {
	case damage:
		reduceHealth(effect.getValue());
		break;

	case healing:
		increaseHealth(effect.getValue());
		break;

	default:
		std::cout << "No effect applied" << std::endl;
		return false;
		break;
	}

	return true;
}

std::vector<Card> Player::getHand() {
	return _hand;
}

std::vector<Card> Player::getGraveyard() {
	return _graveyard;
}

void Player::forceCardIntoHand(Card &card) {
	_hand.erase(_hand.begin());
	_hand.push_back(card);
}