#pragma once
#include "game_parameters.h"
#include "deck.h"

class Player {
public:
	Player(bool isAI, GameSystem system);
	~Player();

	int getPlayerNumber();
	void populateDeck();
	Deck getDeck();
	void reduceHealth(int value);
	int getHealth();

	__event void PlayerKilled(int playerNumber);

protected:
	int _playerNumber;
	Deck _deck;
	int _health;
	bool _isAI;
	GameSystem _system;
	
	std::vector<Card> _hand;
	// Board?
};